#include <avr/io.h>
#include "../lib/bootstrap.h"

DigitalIO *d0 = new DigitalIO(&PORTD,&PIND,&DDRD,PD0);
DigitalIO *d1 = new DigitalIO(&PORTD,&PIND,&DDRD,PD1);
DigitalIO *d2 = new DigitalIO(&PORTD,&PIND,&DDRD,PD2);
DigitalIO *d3 = new DigitalIO(&PORTD,&PIND,&DDRD,PD3,&TCCR2A,COM2B1);
DigitalIO *d4 = new DigitalIO(&PORTD,&PIND,&DDRD,PD4);
DigitalIO *d5 = new DigitalIO(&PORTD,&PIND,&DDRD,PD5,&TCCR1A,COM1A1);
DigitalIO *d6 = new DigitalIO(&PORTD,&PIND,&DDRD,PD6);
DigitalIO *d7 = new DigitalIO(&PORTD,&PIND,&DDRD,PD7);
DigitalIO *d8 = new DigitalIO(&PORTB,&PINB,&DDRB,PB0);
DigitalIO *d9 = new DigitalIO(&PORTB,&PINB,&DDRB,PB1,&TCCR1A,COM1A1);
DigitalIO *d10 = new DigitalIO(&PORTB,&PINB,&DDRB,PB2,&TCCR1A,COM1B1);
DigitalIO *d11 = new DigitalIO(&PORTB,&PINB,&DDRB,PB3,&TCCR2A,COM2A1);
DigitalIO *d12 = new DigitalIO(&PORTB,&PINB,&DDRB,PB4);
DigitalIO *d13 = new DigitalIO(&PORTB,&PINB,&DDRB,PB5);
DigitalIO *d14 = new DigitalIO(&PORTC,&PINC,&DDRC,PC0);
DigitalIO *d15 = new DigitalIO(&PORTC,&PINC,&DDRC,PC1);
DigitalIO *d16 = new DigitalIO(&PORTC,&PINC,&DDRC,PC2);
DigitalIO *d17 = new DigitalIO(&PORTC,&PINC,&DDRC,PC3);