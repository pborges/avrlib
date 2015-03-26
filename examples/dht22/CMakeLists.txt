cmake_minimum_required(VERSION 2.6)

add_avr_executable(dht22 atmega328p 16000000 usbtiny
    main.cpp
    ../../io/digitalio.cpp
    ../../usart/usart.cpp
    ../../bootstrap/bootstrap.cpp
    ../../cron/cron.cpp
    ../../dht22/dht22.cpp
    )