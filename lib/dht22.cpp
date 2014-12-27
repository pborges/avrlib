#include "dht22.h"

#include "../lib/usart.h"
extern USART *usart;

DHT22::DHT22(Cron *cron, DigitalIO *pin) {
	m_cron = cron;
	m_pin = pin;
}

float DHT22::getHumidity() {
	readSensor();
	return humidity;
}

float DHT22::getTemperature() {
	readSensor();
	return temperature;
}

#ifndef OPTIMIZE_SRAM_SIZE

const char* DHT22::getStatusString() {
	switch ( error ) {
		case DHT22::ERROR_TIMEOUT:
			return "TIMEOUT";

		case DHT22::ERROR_CHECKSUM:
			return "CHECKSUM";

		default:
			return "OK";
	}
}

#else

// At the expense of 26 bytes of extra PROGMEM, we save 11 bytes of
// SRAM by using the following method:

prog_char P_OK[]       PROGMEM = "OK";
prog_char P_TIMEOUT[]  PROGMEM = "TIMEOUT";
prog_char P_CHECKSUM[] PROGMEM = "CHECKSUM";

const char *DHT22::getStatusString() {
	prog_char *c;
	switch ( error ) {
		case DHT22::ERROR_CHECKSUM:
			c = P_CHECKSUM; break;

		case DHT22::ERROR_TIMEOUT:
			c = P_TIMEOUT; break;

		default:
			c = P_OK; break;
	}

	static char buffer[9];
	strcpy_P(buffer, c);

	return buffer;
}

#endif

void DHT22::readSensor() {
	unsigned long startTime = m_cron->millis();
	if ( (unsigned long)(startTime - lastReadTime) < 1999L ) {
    	return;
	}
	lastReadTime = startTime;

	temperature = 0;
	humidity = 0;

	// Request sample

	m_pin->setLow();
	m_pin->setOutput();
	// m_cron->delay_us(800);
	_delay_us(800);
	m_pin->setInput();
	m_pin->setHigh();

	// We're going to read 83 edges:
	// - First a FALLING, RISING, and FALLING edge for the start bit
	// - Then 40 bits: RISING and then a FALLING edge per bit
	// To keep our code simple, we accept any HIGH or LOW reading if it's max 85 usecs long

	uint16_t rawHumidity = 0;
	uint16_t rawTemperature = 0;
	uint16_t data = 0;

	for ( int8_t i = -3 ; i < 2 * 40; i++ ) {
		uint8_t age = 0;
		startTime = m_cron->micros();

		do {
			age = (unsigned long)(m_cron->micros() - startTime);
			if ( age > 90 ) {
				// usart->print("AGE: ");
				// usart->print(i);
				// usart->print(" ");
				// usart->println(age);
				error = ERROR_TIMEOUT;
				return;
			}
		}
		while ( m_pin->read() == (i & 1) ? HIGH : LOW );

		if ( i >= 0 && (i & 1) ) {
			// Now we are being fed our 40 bits
			data <<= 1;

			// A zero max 30 usecs, a one at least 68 usecs.
			if ( age > 30 ) {
				data |= 1; // we got a one
			}
		}

		switch ( i ) {
			case 31:
				rawHumidity = data;
				break;
			case 63:
				rawTemperature = data;
				data = 0;
				break;
		}
	}

	// Verify checksum

	if ( (uint8_t)(((uint8_t)rawHumidity) + (rawHumidity >> 8) + ((uint8_t)rawTemperature) + (rawTemperature >> 8)) != data ) {
		error = ERROR_CHECKSUM;
		return;
	}

	// Store readings

	humidity = rawHumidity * 0.1;

	if ( rawTemperature & 0x8000 ) {
		rawTemperature = -(int16_t)(rawTemperature & 0x7FFF);
	}
	temperature = ((int16_t)rawTemperature) * 0.1;

	error = ERROR_NONE;
}
