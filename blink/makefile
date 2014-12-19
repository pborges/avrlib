PROGRAM = main

LIBS = 	$(OUT)/digitalio.o \
		$(OUT)/usart.o \
		$(OUT)/i2c.o

F_CPU = 16000000
MMCU = atmega328p
PROGRAMMER = usbtiny

CFLAGS = -DF_CPU=$(F_CPU) -g -Wall -Os -mmcu=$(MMCU)
OUT = bin
LIB = ../lib

all: $(OUT) libs $(PROGRAM).compile $(PROGRAM).link $(PROGRAM).lst $(PROGRAM).hex

libs:
	avr-g++ $(CFLAGS) -c $(LIB)/digitalio.cpp -o $(OUT)/digitalio.o
	avr-g++ $(CFLAGS) -c $(LIB)/usart.cpp -o $(OUT)/usart.o
	avr-g++ $(CFLAGS) -c $(LIB)/i2c.cpp -o $(OUT)/i2c.o

$(PROGRAM).compile:
	avr-g++ $(CFLAGS) -c $(PROGRAM).cpp -o $(OUT)/$(PROGRAM).o

$(PROGRAM).link:
	avr-g++ -g -mmcu=$(MMCU) -o $(OUT)/$(PROGRAM).elf $(OUT)/$(PROGRAM).o $(LIBS)

$(PROGRAM).lst:
	avr-objdump -h -S $(OUT)/$(PROGRAM).elf > $(OUT)/$(PROGRAM).lst

$(PROGRAM).hex:
	avr-objcopy -j .text -j .data -O ihex $(OUT)/$(PROGRAM).elf $(OUT)/$(PROGRAM).hex


install:  $(PROGRAM).hex
	avrdude -p $(MMCU) -c $(PROGRAMMER) -P usb -v  \
         -U flash:w:$(OUT)/$(PROGRAM).hex 

fuse:
	avrdude -p $(MMCU) -c $(PROGRAMMER) -P usb -v \
	-U lfuse:w:0xc6:m -U hfuse:w:0xd9:m 

clean:
	rm -Rf $(OUT)

$(OUT): 
	mkdir -p $(OUT)