#include "usart.h"

USART::USART(uint16_t baud) {
	m_prescale = (((F_CPU / (baud * 16UL))) - 1);

	/*Set baud rate */
	UBRR0H = (unsigned char)(m_prescale>>8);
	UBRR0L = (unsigned char)m_prescale;
	/*Enable receiver and transmitter */
	UCSR0B = (1<<RXEN0)|(1<<TXEN0);
	/* Set frame format: 8data, 2stop bit */
	UCSR0C = (1<<USBS0)|(3<<UCSZ00);
}
void USART::write(const char *data, uint16_t len) {
	for(uint16_t i=0;i<len;i++){
		this->printc(data[i]);
	}
}

void USART::print(const char *data) {
	this->write(data,strlen(data));
}
void USART::print(char data) {
	this->printc(data);
}
void USART::println(const char *data) {
	this->print(data);
	this->printc(0x0D);
	this->printc(0x0A);
}
void USART::printc(char c) {
	/* Wait for empty transmit buffer */
	while ( !( UCSR0A & (1<<UDRE0)) );
	/* Put data into buffer, sends the data */
	UDR0 = c;
}
void USART::print(long data, uint8_t radix) {
	char str[32]; // this could cause a buffer overflow on a large number in BIN mode
	uint8_t i = 0;
	ltoa(data,str,radix);
	while (str[i]) {
		str[i] = toupper(str[i]);
		i++;
	}
	this->print(str);
}
void USART::println(long data, uint8_t radix) {
	this->print(data,radix);
	this->printc(0x0D);
	this->printc(0x0A);
}
void USART::println(char data) {
	this->printc(data);
	this->printc(0x0D);
	this->printc(0x0A);
}
bool USART::available() {
	return (UCSR0A & (1<<RXC0));
}
char USART::read() {
	/* Wait for data to be received */
	while ( !this->available() ){};
	/* Get and return received data from buffer */
	return UDR0;
}