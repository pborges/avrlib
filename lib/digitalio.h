#ifndef __DIGITAL_IO_H
#define __DIGITAL_IO_H

#include <avr/io.h>
#include <stdlib.h>

class DigitalIO {
private:
	volatile uint8_t *m_port;
	volatile uint8_t *m_pin;
	volatile uint8_t *m_ddr;
	uint8_t m_mask;
public:
	DigitalIO(volatile uint8_t* port, volatile uint8_t* pin, volatile uint8_t* ddr, uint8_t mask);
	void setHigh();
	void setLow();

	void setOutput();
	void setInput();

	void toggle();

	bool read();
};

#endif