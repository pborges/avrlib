cmake_minimum_required(VERSION 2.6)

add_avr_executable(serial atmega328p 16000000 usbtiny
    main.cpp
    ../lib/digitalio.cpp
    ../lib/usart.cpp
    ../lib/bootstrap.cpp
    ../lib/cron.cpp
    )