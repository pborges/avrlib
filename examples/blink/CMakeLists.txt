cmake_minimum_required(VERSION 2.6)

add_avr_executable(blink atmega328p 16000000 usbtiny
    main.cpp
    ../../io/digitalio.cpp
    )