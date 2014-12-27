// Ported by Paulo Borges 
// from Rob Tillaart @ http://arduino.cc/playground/Main/DHTLib

#ifndef _DHT22_H__
#define _DHT22_H__

#include "digitalio.h"
#include "cron.h"

class DHT22 {
public:
	typedef enum {
		ERROR_NONE = 0,
		ERROR_TIMEOUT,
		ERROR_CHECKSUM
	} DHT_ERROR_t;

	DHT22(Cron *cron, DigitalIO *pin);

	float getTemperature();
	float getHumidity();

	DHT_ERROR_t getStatus() { return error; };
	const char* getStatusString();

	int getMinimumSamplingPeriod() { return 2000; }

	int8_t getNumberOfDecimalsTemperature() { return 0; };
	int8_t getLowerBoundTemperature() { return 0; };
	int8_t getUpperBoundTemperature() { return 50; };

	int8_t getNumberOfDecimalsHumidity() { return 0; };
	int8_t getLowerBoundHumidity() { return 20; };
	int8_t getUpperBoundHumidity() { return 90; };

	static float toFahrenheit(float fromCelcius) { return 1.8 * fromCelcius + 32.0; };
	static float toCelsius(float fromFahrenheit) { return (fromFahrenheit - 32.0) / 1.8; };

protected:
	void readSensor();

	float temperature;
	float humidity;

	DigitalIO *m_pin;
	Cron *m_cron;

private:
	DHT_ERROR_t error;
	unsigned long lastReadTime;
};

#endif

