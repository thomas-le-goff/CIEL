#!/usr/bin/env python

import paho.mqtt.client as mqtt
import argparse
import socket
import logging
import time

from nmea import GPRMC

MQTT_BROKER_ENDPOINT = "0.0.0.0:1883"
NMEA_UDP_SOCKET = "127.0.0.1:10110"


class Program:
    vessel_id: int
    nmea_socket: socket
    mqttc: mqtt.Client

    def __init__(self, vessel_id: int):
        self.vessel_id = vessel_id

    def __enter__(self):
        # UDP Setup
        nmea_address, nmea_port = tuple(NMEA_UDP_SOCKET.split(":"))

        self.nmea_socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
        self.nmea_socket.bind((nmea_address, int(nmea_port)))

        # MQTT Setup
        mqtt_address, mqtt_port = tuple(MQTT_BROKER_ENDPOINT.split(":"))

        self.mqttc = mqtt.Client(mqtt.CallbackAPIVersion.VERSION2)
        self.mqttc.connect(mqtt_address, int(mqtt_port), 60)

        # Start communication with MQTT broker
        self.mqttc.loop_start()

        return self

    def __exit__(self, exc_type, exc_value, traceback):
        # Stop communication with MQTT broker
        self.mqttc.loop_stop()

        self.mqttc.disconnect()
        self.nmea_socket.close()

    def loop(self):
        while True:
            try:
                # Read from UDP Socket
                nmea_data = self.nmea_socket.recv(1024)

                gprmc = None
                if nmea_data:
                    logging.debug(f"Read NMEA trame from UDP: {nmea_data}")
                    # Try decoding into GPRMC
                    try:
                        gprmc = GPRMC.parse(nmea_data.decode())
                    except ValueError as err:
                        pass
                    except RuntimeError as err:
                        # TODO better error handling
                        logging.warning(err)

                if gprmc:
                    topic = f"vessels/{self.vessel_id}/gprmc"
                    payload = gprmc.to_json()
                    self.mqttc.publish(topic, payload)
                    logging.debug(f"Sent message: {payload} on topic: {topic}")
            except KeyboardInterrupt:
                break
            except RuntimeError as err:
                logging.error(err)

            time.sleep(0.3)


# Entrypoint
def main():
    parser = argparse.ArgumentParser()

    parser.add_argument("--vessel-id", dest="vessel_id", type=str, required=True)
    parser.add_argument("-v", "--verbose", dest="verbose", action="store_true")

    args = parser.parse_args()

    logging.basicConfig(
        format="%(levelname)s [%(asctime)s] %(name)s - %(message)s",
        datefmt="%Y-%m-%d %H:%M:%S",
        level=logging.DEBUG if args.verbose else logging.ERROR,
    )

    with Program(args.vessel_id) as program:
        program.loop()


if __name__ == "__main__":
    main()
