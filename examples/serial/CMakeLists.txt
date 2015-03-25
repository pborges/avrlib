cmake_minimum_required(VERSION 2.6)

add_avr_executable(serial atmega328p 16000000 usbtiny
    main.cpp
    ../../digitalio.cpp
    ../../usart.cpp
    ../../bootstrap.cpp
    ../../cron.cpp
    )