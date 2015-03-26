#include "digitalio.h"

DigitalIO::DigitalIO(){}
DigitalIO::DigitalIO(volatile uint8_t* port, volatile uint8_t* pin, volatile uint8_t* ddr, uint8_t mask) {
	m_port = port;
	m_pin = pin;
	m_ddr = ddr;
	m_mask = mask;
}
DigitalIO::DigitalIO(volatile uint8_t* port, volatile uint8_t* pin, volatile uint8_t* ddr, uint8_t mask, volatile uint8_t* timer_register, uint8_t timer_mask) {
	m_port = port;
	m_pin = pin;
	m_ddr = ddr;
	m_mask = mask;
	m_timer_register = timer_register;
	m_timer_mask = timer_mask;
}

void DigitalIO::setHigh() {
	uint8_t oldSREG = SREG;
	cli();
	*m_port |= (1 << m_mask);
	SREG = oldSREG;
}
void DigitalIO::setLow() {
	uint8_t oldSREG = SREG;
	cli();
	*m_port &= ~(1 << m_mask);
	SREG = oldSREG;
}
void DigitalIO::toggle() {
	uint8_t oldSREG = SREG;
	cli();
	*m_port ^= (1 << m_mask);
	SREG = oldSREG;
}

void DigitalIO::setInput() {
	disablePwm();
	*m_port |= (1 << m_mask);
	*m_ddr &= ~(1 << m_mask);
}

void DigitalIO::setOutput() {
	disablePwm();
	*m_ddr |= (1 << m_mask);
}

uint8_t DigitalIO::read() {
	if (*m_pin & (1 << m_mask)) return HIGH;
	return LOW;
}

void DigitalIO::disablePwm(){
	if(m_timer_register != NULL) {
		*m_timer_register &= (1 << m_timer_mask);
	}
}