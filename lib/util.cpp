#include "util.h"

void delay_ms(unsigned int msec) {
	for(unsigned int i = 0; i < msec; i++) {
		_delay_ms(1);
	}
}

void delay_us(unsigned int usec) {
	for(unsigned int i = 0; i < usec; i++) {
		_delay_us(1);
	}
}