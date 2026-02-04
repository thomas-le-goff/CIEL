#!/usr/bin/env python3

import socket
import argparse

DEFAULT_HOST = "127.0.0.1"
DEFAULT_PORT = 10110

def main():
    parser = argparse.ArgumentParser(description="UDP Receiver")
    parser.add_argument("--host", default=DEFAULT_HOST)
    parser.add_argument("--port", type=int, default=DEFAULT_PORT)

    args = parser.parse_args()

    print(f"Listening on UDP {args.host}:{args.port}")

    sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    sock.bind((args.host, args.port))

    try:
        while True:
            data, addr = sock.recvfrom(1024)
            message = data.decode(errors="ignore")

            print(f"[FROM {addr}] {message}")

    except KeyboardInterrupt:
        print("\nStopping UDP receiver...")
    finally:
        sock.close()


if __name__ == "__main__":
    main()