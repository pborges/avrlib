#include <avr/io.h>
#include "../../bootstrap/bootstrap.h"
#include "../../dht22/dht22.h"
#include "../../usart/usart.h"


Cron cron;
USART usart(9600);
DigitalIO dht_pin(&PORTB, &PINB, &DDRB, PB1);

int main() {
    usart.println("#Listening");

    DHT22 dht(cron, dht_pin);

    while (1) {
        usart.print("TEMP: ");
        usart.print(dht.toFahrenheit(dht.getTemperature()));
        usart.println(" F ");
        usart.print("HUMIDITY: ");
        usart.println(dht.getHumidity());
        usart.println(dht.getStatusString());
        cron.delay_ms(2000);
    }
}