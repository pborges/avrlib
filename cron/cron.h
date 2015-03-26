#ifndef __CRON_H__
#define __CRON_H__

#include <avr/interrupt.h>
#include <util/delay.h>

#define clockCyclesPerMicrosecond() ( F_CPU / 1000000L )
#define clockCyclesToMicroseconds(a) ( (a) / clockCyclesPerMicrosecond() )
#define microsecondsToClockCycles(a) ( (a) * clockCyclesPerMicrosecond() )

// the prescaler is set so that timer0 ticks every 64 clock cycles, and the
// the overflow handler is called every 256 ticks.
#define MICROSECONDS_PER_TIMER0_OVERFLOW (clockCyclesToMicroseconds(64 * 256))

// the whole number of milliseconds per timer0 overflow
#define MILLIS_INC (MICROSECONDS_PER_TIMER0_OVERFLOW / 1000)

// the fractional number of milliseconds per timer0 overflow. we shift right
// by three to fit these numbers into a byte. (for the clock speeds we care
// about - 8 and 16 MHz - this doesn't lose precision.)
#define FRACT_INC ((MICROSECONDS_PER_TIMER0_OVERFLOW % 1000) >> 3)
#define FRACT_MAX (1000 >> 3)

class Cron {
private:
	volatile unsigned long timer0_overflow_count = 0;
	volatile unsigned long timer0_millis = 0;
	unsigned char timer0_fract = 0;
protected:
	static Cron* self;
public:
	Cron();
	unsigned long millis();
	unsigned long micros();
	void interruptHandler();
	static void isr();

	static void delay_ms(unsigned int msec);
	static void delay_us(unsigned int usec);
};

#endif