#!/usr/bin/env python3

import socket
import argparse
import paho.mqtt.client as mqtt

DEFAULT_UDP_HOST = "127.0.0.1"
DEFAULT_UDP_PORT = 10110
DEFAULT_MQTT_BROKER = "10.0.22.11"
DEFAULT_MQTT_PORT = 1883

def main():
    parser = argparse.ArgumentParser(description="UDP Receiver")
    parser.add_argument("--host", default=DEFAULT_UDP_HOST)
    parser.add_argument("--udp-port", dest="udp_port", type=int, default=DEFAULT_UDP_PORT)
    parser.add_argument("--broker", default=DEFAULT_MQTT_BROKER)
    parser.add_argument("--mqtt-port", dest="mqtt_port", type=int, default=DEFAULT_MQTT_PORT)
    parser.add_argument("--topic", required=True)

    args = parser.parse_args()

    print(f"Listening on UDP {args.host}:{args.udp_port}")

    # UDP
    sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    sock.bind((args.host, args.udp_port))

    # MQTT
    client = mqtt.Client()
    client.connect(args.broker, args.mqtt_port, 60)

    try:
        while True:
            data, addr = sock.recvfrom(1024)
            if len(data) > 0:
                msg = data.decode(errors="ignore")
                msg_splitted = msg.split(',')
                if len(msg_splitted) > 0 and msg_splitted[0] == "$GPRMC":
                    client.publish(args.topic, msg)

    except KeyboardInterrupt:
        print("\nStopping...")
    finally:
        sock.close()
        client.disconnect()


if __name__ == "__main__":
    main()