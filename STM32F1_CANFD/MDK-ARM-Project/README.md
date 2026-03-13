# serial_comm

Small C program to send/receive data over a USB-serial device (e.g. /dev/ttyUSB0).

Features:
- Reads data from the USB tty and writes stdin lines to the serial port.
- When received data contains the substring "111", prints "OK" to stdout.

Build:

```sh
make
```

Run (example):

```sh
sudo ./serial_comm /dev/ttyUSB0 115200
```

Notes:
- Adjust device and baud rate as needed. You may need `sudo` to access `/dev/ttyUSB0`.
- On Raspberry Pi 5 running Linux, the device name is typically `/dev/ttyUSB0` or `/dev/ttyACM0`.
