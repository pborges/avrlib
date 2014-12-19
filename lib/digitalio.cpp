#include "digitalio.h"

DigitalIO::DigitalIO(volatile uint8_t* port, volatile uint8_t* pin, volatile uint8_t* ddr, uint8_t mask) {
	m_port = port;
	m_pin = pin;
	m_ddr = ddr;
	m_mask = mask;
}

void DigitalIO::setHigh() {
	*m_port |= (1 << m_mask);
}
void DigitalIO::setLow() {
	*m_port &= ~(1 << m_mask);
}
void DigitalIO::toggle() {
	*m_port ^= m_mask;
}

void DigitalIO::setInput() {
	*m_ddr &= ~m_mask;
}
void DigitalIO::setOutput() {
	*m_ddr |= (1 << m_mask);
}

bool DigitalIO::read() {
	return (*m_pin & m_mask) << m_mask;
}