#include <avr/io.h>
#include <util/delay.h>
#include "../lib/digitalio.h"

DigitalIO led(&PORTB,&PINB,&DDRB,PB2);

int main() {
	led.setOutput();

	while(1) {
		led.toggle();
		_delay_ms(1000);
	}	
}