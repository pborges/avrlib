#include "usart.h"

USART::USART() {
}

USART::USART(unsigned long baud) {
    init(baud);
}

void USART::init(unsigned long baud) {
    prescale_ = (((F_CPU / (baud * 16UL))) - 1);

    /*Set baud rate */
    UBRR0H = (unsigned char) (prescale_ >> 8);
    UBRR0L = (unsigned char) prescale_;
    /*Enable receiver and transmitter */
    UCSR0B = (1 << RXEN0) | (1 << TXEN0);
    /* Set frame format: 8data, 2stop bit */
    UCSR0C = (1 << USBS0) | (3 << UCSZ00);
}

void USART::write(const char *data, uint16_t len) {
    for (uint16_t i = 0; i < len; i++) {
        this->printc(data[i]);
    }
}

void USART::print(const char *data) {
    write(data, strlen(data));
}

void USART::print(char data) {
    printc(data);
}

void USART::println() {
    printc(0x0D);
    printc(0x0A);
}

void USART::println(const char *data) {
    print(data);
    println();
}

void USART::printc(char c) {
    /* Wait for empty transmit buffer */
    while (!(UCSR0A & (1 << UDRE0)));
    /* Put data into buffer, sends the data */
    UDR0 = (uint8_t) c;
}

void USART::print(double data, uint8_t digits) {
    // Handle negative numbers
    if (data < 0.0) {
        print('-');
        data = -data;
    }

    // Round correctly so that print(1.999, 2) prints as "2.00"
    double rounding = 0.5;
    for (uint8_t i = 0; i < digits; ++i)
        rounding /= 10.0;

    data += rounding;

    // Extract the integer part of the data and print it
    unsigned long int_part = (unsigned long) data;
    double remainder = data - (double) int_part;
    print(int_part);

    // Print the decimal point, but only if there are digits beyond
    if (digits > 0) {
        print(".");
    }

    // Extract digits from the remainder one at a time
    while (digits-- > 0) {
        remainder *= 10.0;
        int toPrint = int(remainder);
        print(toPrint);
        remainder -= toPrint;
    }
}

void USART::println(double data, uint8_t digits) {
    print(data, digits);
    printc(0x0D);
    printc(0x0A);
}

void USART::print(int data, uint8_t radix) {
    char str[32]; // this could cause a buffer overflow on a large number in BIN mode
    uint8_t i = 0;
    ltoa(data, str, radix);
    while (str[i]) {
        str[i] = (char) toupper(str[i]);
        i++;
    }
    this->print(str);
}

void USART::println(int data, uint8_t radix) {
    print(data, radix);
    printc(0x0D);
    printc(0x0A);
}

void USART::print(long data, uint8_t radix) {
    char str[32]; // this could cause a buffer overflow on a large number in BIN mode
    uint8_t i = 0;
    ltoa(data, str, radix);
    while (str[i]) {
        str[i] = (char) toupper(str[i]);
        i++;
    }
    this->print(str);
}

void USART::println(long data, uint8_t radix) {
    this->print(data, radix);
    this->printc(0x0D);
    this->printc(0x0A);
}

void USART::print(unsigned long data, uint8_t radix) {
    char str[32]; // this could cause a buffer overflow on a large number in BIN mode
    uint8_t i = 0;
    ltoa(data, str, radix);
    while (str[i]) {
        str[i] = (char) toupper(str[i]);
        i++;
    }
    print(str);
}

void USART::println(unsigned long data, uint8_t radix) {
    this->print(data, radix);
    this->printc(0x0D);
    this->printc(0x0A);
}

void USART::println(char data) {
    printc(data);
    printc(0x0D);
    printc(0x0A);
}

bool USART::available() {
    return (UCSR0A & (1 << RXC0)) > 0;
}

char USART::read() {
    /* Wait for data to be received */
    while (!this->available()) {};
    /* Get and return received data from buffer */
    return (char) UDR0;
}