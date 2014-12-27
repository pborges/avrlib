PROGRAM = main

LIBS =	$(OUT)/dht22.o \
		$(OUT)/usart.o \
		$(OUT)/digitalio.o \
		$(OUT)/cron.o \
		$(OUT)/bootstrap.o

F_CPU = 16000000
MMCU = atmega328p
PROGRAMMER = usbtiny

CFLAGS = -DF_CPU=$(F_CPU) -g -Wall -Os -mmcu=$(MMCU) -std=gnu++11
OUT = bin
LIB = 	../lib

all: $(OUT) libs $(PROGRAM).compile $(PROGRAM).link $(PROGRAM).lst $(PROGRAM).hex

libs:
	avr-g++ $(CFLAGS) -c $(LIB)/usart.cpp -o $(OUT)/usart.o
	avr-g++ $(CFLAGS) -c $(LIB)/dht22.cpp -o $(OUT)/dht22.o
	avr-g++ $(CFLAGS) -c $(LIB)/digitalio.cpp -o $(OUT)/digitalio.o
	avr-g++ $(CFLAGS) -c $(LIB)/cron.cpp -o $(OUT)/cron.o
	avr-g++ $(CFLAGS) -c $(LIB)/bootstrap.cpp -o $(OUT)/bootstrap.o

$(PROGRAM).compile:
	avr-g++ $(CFLAGS) -c $(PROGRAM).cpp -o $(OUT)/$(PROGRAM).o

$(PROGRAM).link:
	avr-g++ $(CFLAGS) -mmcu=$(MMCU) -o $(OUT)/$(PROGRAM).elf $(OUT)/$(PROGRAM).o $(LIBS)

$(PROGRAM).lst:
	avr-objdump -h -S $(OUT)/$(PROGRAM).elf > $(OUT)/$(PROGRAM).lst

$(PROGRAM).hex:
	avr-objcopy -j .text -j .data -O ihex $(OUT)/$(PROGRAM).elf $(OUT)/$(PROGRAM).hex


install:  $(PROGRAM).hex
	avrdude -p $(MMCU) -c $(PROGRAMMER) -P usb -v  \
         -U flash:w:$(OUT)/$(PROGRAM).hex 

fuse:
	avrdude -p $(MMCU) -c $(PROGRAMMER) -P usb -v -b 19200 \
	-U lfuse:w:0xff:m \
	-U hfuse:w:0xde:m \
	-U efuse:w:0x05:m

clean:
	rm -Rf $(OUT)

$(OUT): 
	mkdir -p $(OUT)