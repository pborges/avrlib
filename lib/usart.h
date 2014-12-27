#ifndef __UART_H__
#define __UART_H__

#include <avr/io.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define HEX 16
#define DEC 10
#define BIN 2

class USART {
private:
	uint16_t m_prescale;
	void init(uint16_t baud);
public:
	USART();
	USART(uint16_t baud);

	void write(const char *data, uint16_t len);

	void println(const char *data);
	void println(char data);
	void print(const char *data);
	void print(char data);
	void printc(char c);

	void println(long data, uint8_t radix=DEC);
	void print(long data, uint8_t radix=DEC);

	void println(double data, uint8_t digits = 2);
	void print(double data, uint8_t digits = 2);

	void println(unsigned long data, uint8_t radix=DEC);
	void print(unsigned long data, uint8_t radix=DEC);

	void println(int data, uint8_t radix=DEC);
	void print(int data, uint8_t radix=DEC);

	bool available();

	char read();
};

#endif