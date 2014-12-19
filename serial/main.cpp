#include <avr/io.h>
#include <util/delay.h>
#include "../lib/usart.h"

USART usart(9600);
int main() {
	while(1){
		if(usart.available()) {
			usart.print(usart.read());
		}
	}
}