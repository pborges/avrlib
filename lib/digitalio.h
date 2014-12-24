#ifndef __DIGITAL_IO_H
#define __DIGITAL_IO_H

#include <avr/interrupt.h>
#include <avr/io.h>
#include <stdlib.h>

#define HIGH 	1
#define LOW 	0

class DigitalIO {
private:
	volatile uint8_t *m_port;
	volatile uint8_t *m_pin;
	volatile uint8_t *m_ddr;
	volatile uint8_t *m_timer_register;
	uint8_t m_timer_mask;
	uint8_t m_mask;

	void disablePwm();
public:
	DigitalIO();
	DigitalIO(volatile uint8_t* port, volatile uint8_t* pin, volatile uint8_t* ddr, uint8_t mask);
	DigitalIO(volatile uint8_t* port, volatile uint8_t* pin, volatile uint8_t* ddr, uint8_t mask, volatile uint8_t* timer_register, uint8_t timer_mask);
	
	void setHigh();
	void setLow();

	void setOutput();
	void setInput();
	void setInputPullup();

	void toggle();

	bool read();
};

#endif