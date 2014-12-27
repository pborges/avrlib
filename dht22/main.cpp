#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "../lib/bootstrap.h"
#include "../lib/dht22.h"
#include "../lib/usart.h"
#include "../lib/cron.h"


Cron *cron = new Cron();
USART *usart = new USART(9600);
DigitalIO *dht_pin = new DigitalIO(&PORTB,&PINB,&DDRB,PB1);

int main() {
	usart->println("#Listening");

	DHT22 *dht = new DHT22(cron,dht_pin);

	while(1){
		usart->print("TEMP: ");
		usart->print(dht->toFahrenheit(dht->getTemperature()));
		usart->println(" F ");
		usart->print("HUMIDITY: ");
		usart->println(dht->getHumidity());
		usart->println(dht->getStatusString());
		cron->delay_ms(2000);
	}
}