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
	*m_ddr &= ~(1 << m_mask);
}

void DigitalIO::setInputPullup() {
	this->setInput();
	this->setHigh();
}

void DigitalIO::setOutput() {
	disablePwm();
	*m_ddr |= (1 << m_mask);
}

bool DigitalIO::read() {
	return ((*m_pin & m_mask) << m_mask) > 0;
}

void DigitalIO::disablePwm(){
	if(m_timer_register != NULL) {
		*m_timer_register &= (1 << m_timer_mask);
	}
}