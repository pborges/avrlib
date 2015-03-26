#include <avr/io.h>
#include "../../usart/usart.h"

USART usart(57600);
int main() {
	while(1){
		if(usart.available()) {
			usart.print(usart.read());
		}
	}
}