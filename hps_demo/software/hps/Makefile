TARGET = hps_demo

CROSS_COMPILE = arm-linux-gnueabihf-
# $(SOCEDS_DEST_ROOT) is provided by the embedded_command_shell.sh
CFLAGS = -g -Wall -I $(SOCEDS_DEST_ROOT)/ip/altera/hps/altera_hps/hwlib/include
LDFLAGS = -g -Wall
CC = $(CROSS_COMPILE)gcc
ARCH=arm

build: $(TARGET)

$(TARGET): main.o
	$(CC) $(LDFLAGS) $^ -o $@

%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: clean
clean:
	rm -f $(TARGET) *.a *.o *~