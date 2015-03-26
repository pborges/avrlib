//
// Created by pborges on 3/25/15.
//

#include "spi.h"

SPI::SPI(DigitalIO &sck, DigitalIO &miso, DigitalIO &mosi, DigitalIO &slave_select) {
    sck_ = sck;
    miso_ = miso;
    mosi_ = mosi;
    slave_select_ = slave_select;
}

uint8_t SPI::transfer(uint8_t _data) {
    SPDR = _data;
    while (!(SPSR & _BV(SPIF)));
    return SPDR;
}

void SPI::attachInterrupt() {
    SPCR |= _BV(SPIE);
}

void SPI::detachInterrupt() {
    SPCR &= ~_BV(SPIE);
}

void SPI::begin() {
    miso_.setInput();

    // Set SS to high so a connected chip will be "deselected" by default
//    digitalWrite(SS, HIGH);
    slave_select_.setHigh();

    // When the SS pin is set as OUTPUT, it can be used as
    // a general purpose output port (it doesn't influence
    // SPI operations).
//    pinMode(SS, OUTPUT);
    slave_select_.setOutput();

    // Warning: if the SS pin ever becomes a LOW INPUT then SPI
    // automatically switches to Slave, so the data direction of
    // the SS pin MUST be kept as OUTPUT.
    SPCR |= _BV(MSTR);
    SPCR |= _BV(SPE);

    // Set direction register for SCK and MOSI pin.
    // MISO pin automatically overrides to INPUT.
    // By doing this AFTER enabling SPI, we avoid accidentally
    // clocking in a single bit since the lines go directly
    // from "input" to SPI control.
    // http://code.google.com/p/arduino/issues/detail?id=888
//    pinMode(SCK, OUTPUT);
    sck_.setOutput();
//    pinMode(MOSI, OUTPUT);
    mosi_.setOutput();
}


void SPI::end() {
    SPCR &= ~_BV(SPE);
}

void SPI::setBitOrder(uint8_t bitOrder) {
    if (bitOrder == LSBFIRST) {
        SPCR |= _BV(DORD);
    } else {
        SPCR &= ~(_BV(DORD));
    }
}

void SPI::setDataMode(uint8_t mode) {
    SPCR = (SPCR & ~SPI_MODE_MASK) | mode;
}

void SPI::setClockDivider(uint8_t rate) {
    SPCR = (SPCR & ~SPI_CLOCK_MASK) | (rate & SPI_CLOCK_MASK);
    SPSR = (SPSR & ~SPI_2XCLOCK_MASK) | ((rate >> 2) & SPI_2XCLOCK_MASK);
}
