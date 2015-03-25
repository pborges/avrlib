# DONT CHANGE
set(CMAKE_VERBOSE_MAKEFILE false)
SET(CMAKE_SYSTEM_NAME Generic)
SET(CMAKE_SYSTEM_VERSION 1)

SET(CMAKE_C_COMPILER   /usr/bin/avr-gcc)
SET(CMAKE_CXX_COMPILER /usr/bin/avr-g++)
set(CMAKE_OBJCOPY /usr/bin/avr-objcopy)
set(CMAKE_OBJDUMP /usr/bin/avr-objdump)
SET(CMAKE_FIND_ROOT_PATH  /usr/lib/avr)
SET(AVRDUDE /usr/bin/avrdude)
SET(AVRSIZE  /usr/bin/avr-size)

set(CMAKE_SHARED_LIBRARY_LINK_C_FLAGS "")
set(CMAKE_SHARED_LIBRARY_LINK_CXX_FLAGS "")
SET(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
SET(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
SET(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)

function(add_avr_executable EXECUTABLE_NAME MMCU F_CPU AVR_PROGRAMMER)
    set(elf_file ${EXECUTABLE_NAME}-${MMCU}.elf)
    set(obj_file ${EXECUTABLE_NAME}-${MMCU}.obj)
    set(hex_file ${EXECUTABLE_NAME}-${MMCU}.hex)
    set(map_file ${EXECUTABLE_NAME}-${MMCU}.map)
    add_executable(${elf_file} EXCLUDE_FROM_ALL ${ARGN})
    set(common_opts "-mmcu=${MMCU} -DF_CPU=${F_CPU} -fshort-enums -fpack-struct -Os -Wall -std=c++11")
    set_target_properties(
        ${elf_file}
        PROPERTIES
            COMPILE_FLAGS "${common_opts}"
            LINK_FLAGS "${common_opts} -Wl,-Map,${map_file}"
    )

    add_custom_target(${hex_file}
        ${CMAKE_OBJCOPY} -j .text -j .data -O ihex ${elf_file} ${hex_file}
        DEPENDS ${elf_file}
        COMMENT "Creating Intel Hex File"
        )
    add_custom_command(TARGET ${hex_file} POST_BUILD
        COMMAND
            ${AVRSIZE} ${elf_file}
    )
    add_custom_target(${EXECUTABLE_NAME}_upload
        ${AVRDUDE} -p ${MMCU} -c ${AVR_PROGRAMMER} -P usb -v -U flash:w:${hex_file}
        DEPENDS ${hex_file}
        COMMENT "Uploading ${hex_file} to ${MMCU} using programmer ${AVR_PROGRAMMER}"
        )
endfunction(add_avr_executable)
# END DONT CHANGE
