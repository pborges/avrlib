#include <util/delay.h>
#include "../../io/digitalio.h"

DigitalIO d13(&PORTB, &PINB, &DDRB, PB5);

int main() {

    while (1) {
        d13.toggle();
        _delay_ms(250);
    }
}