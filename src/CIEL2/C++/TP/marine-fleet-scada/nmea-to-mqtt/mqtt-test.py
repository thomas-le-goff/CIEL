#!/usr/bin/env python3

import paho.mqtt.client as mqtt
import argparse
import time

DEFAULT_BROKER = "127.0.0.1"
DEFAULT_PORT = 1883
DEFAULT_TOPIC = "test/topic"


def main():
    parser = argparse.ArgumentParser(description="MQTT Sender")
    parser.add_argument("--broker", default=DEFAULT_BROKER)
    parser.add_argument("--port", type=int, default=DEFAULT_PORT)
    parser.add_argument("--topic", default=DEFAULT_TOPIC)
    parser.add_argument("--message", default="Hello MQTT")

    args = parser.parse_args()

    client = mqtt.Client()
    client.connect(args.broker, args.port, 60)

    print(f"Connected to MQTT broker {args.broker}:{args.port}")
    print(f"Publishing to topic: {args.topic}")

    try:
        while True:
            client.publish(args.topic, args.message)
            print(f"Sent: {args.message}")
            time.sleep(1)

    except KeyboardInterrupt:
        print("\nStopping MQTT sender...")
    finally:
        client.disconnect()


if __name__ == "__main__":
    main()