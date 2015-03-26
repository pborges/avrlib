//
// Created by pborges on 3/25/15.
//

#ifndef _AVR_SPI_H_
#define _AVR_SPI_H_

#include "../io/digitalio.h"

#define LSBFIRST 1
#define MSBFIRST 0

#define SPI_CLOCK_DIV4 0x00
#define SPI_CLOCK_DIV16 0x01
#define SPI_CLOCK_DIV64 0x02
#define SPI_CLOCK_DIV128 0x03
#define SPI_CLOCK_DIV2 0x04
#define SPI_CLOCK_DIV8 0x05
#define SPI_CLOCK_DIV32 0x06
//#define SPI_CLOCK_DIV64 0x07

#define SPI_MODE0 0x00
#define SPI_MODE1 0x04
#define SPI_MODE2 0x08
#define SPI_MODE3 0x0C

#define SPI_MODE_MASK 0x0C  // CPOL = bit 3, CPHA = bit 2 on SPCR
#define SPI_CLOCK_MASK 0x03  // SPR1 = bit 1, SPR0 = bit 0 on SPCR
#define SPI_2XCLOCK_MASK 0x01  // SPI2X = bit 0 on SPSR

class SPI {
public:
    SPI(DigitalIO &, DigitalIO &, DigitalIO &, DigitalIO &);

    uint8_t transfer(uint8_t);

    void attachInterrupt();

    void detachInterrupt();

    void begin(); // Default
    void end();

    void setBitOrder(uint8_t);

    void setDataMode(uint8_t);

    void setClockDivider(uint8_t);

private:
    DigitalIO mosi_;
    DigitalIO miso_;
    DigitalIO sck_;
    DigitalIO slave_select_;
};

#endif //_AVR_SPI_H_
