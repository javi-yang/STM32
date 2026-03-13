CC = gcc
CFLAGS = -Wall -O2
TARGET = serial_comm

all: $(TARGET)

$(TARGET): serial_comm.c
	$(CC) $(CFLAGS) -o $(TARGET) serial_comm.c

clean:
	rm -f $(TARGET)
