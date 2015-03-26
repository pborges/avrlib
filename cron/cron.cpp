#include "cron.h"

Cron* Cron::self;

extern int t;

ISR(TIMER0_OVF_vect) {
	Cron::isr();
}

Cron::Cron() {
	Cron::self = this;

	// this needs to be called before setup() or some functions won't
	// work there
	sei();
	
	// on the ATmega168, timer 0 is also used for fast hardware pwm
	// (using phase-correct PWM would mean that timer 0 overflowed half as often
	// resulting in different millis() behavior on the ATmega8 and ATmega168)
	TCCR0A |= (1 << WGM01);
	TCCR0A |= (1 << WGM00);  

	// set timer 0 prescale factor to 64

	// this combination is for the standard 168/328/1280/2560
	TCCR0B |= (1 << CS01);
	TCCR0B |= (1 << CS00);
	// this combination is for the __AVR_ATmega645__ series
	TCCR0A |= (1 << CS01);
	TCCR0A |= (1 << CS00);

	// enable timer 0 overflow interrupt
	TIMSK0 |= (1 << TOIE0);

	// timers 1 and 2 are used for phase-correct hardware pwm
	// this is better for motors as it ensures an even waveform
	// note, however, that fast pwm mode can achieve a frequency of up
	// 8 MHz (with a 16 MHz clock) at 50% duty cycle

	TCCR1B = 0;

	// set timer 1 prescale factor to 64
	TCCR1B |= (1 << CS11);
	TCCR1B |= (1 << CS10);

	// put timer 1 in 8-bit phase correct pwm mode
	TCCR1A |= (1 << WGM10);

	// set timer 2 prescale factor to 64
	TCCR2B |= (1 << CS22);

	// configure timer 2 for phase correct pwm (8-bit)
	TCCR2A |= (1 << WGM20);

	// set a2d prescale factor to 128
	// 16 MHz / 128 = 125 KHz, inside the desired 50-200 KHz range.
	// XXX: this will not work properly for other clock speeds, and
	// this code should use F_CPU to determine the prescale factor.
	ADCSRA |= (1 << ADPS2);
	ADCSRA |= (1 << ADPS1);
	ADCSRA |= (1 << ADPS0);

	// enable a2d conversions
	ADCSRA |= (1 << ADEN);

	UCSR0B = 0;
}

void Cron::interruptHandler() {
	// copy these to local variables so they can be stored in registers
	// (volatile variables must be read from memory on every access)
	unsigned long m = timer0_millis;
	unsigned char f = timer0_fract;

	m += MILLIS_INC;
	f += FRACT_INC;
	if (f >= FRACT_MAX) {
		f -= FRACT_MAX;
		m += 1;
	}

	timer0_fract = f;
	timer0_millis = m;
	timer0_overflow_count++;
}
void Cron::isr() {
	self->interruptHandler();
}


unsigned long Cron::millis() {
	unsigned long m;
	uint8_t oldSREG = SREG;

	// disable interrupts while we read timer0_millis or we might get an
	// inconsistent value (e.g. in the middle of a write to timer0_millis)
	cli();
	m = timer0_millis;
	SREG = oldSREG;

	return m;
}

unsigned long Cron::micros() {
	unsigned long m;
	uint8_t oldSREG = SREG, t;
	
	cli();
	m = timer0_overflow_count;

	t = TCNT0;

	if ((TIFR0 & _BV(TOV0)) && (t < 255))
		m++;

	SREG = oldSREG;
	
	return ((m << 8) + t) * (64 / clockCyclesPerMicrosecond());
}

void Cron::delay_ms(unsigned int msec) {
	for(unsigned int i = 0; i < msec; i++) {
		_delay_ms(1);
	}
}

void Cron::delay_us(unsigned int usec) {
	for(unsigned int i = 0; i < usec; i++) {
		_delay_us(1);
	}
}