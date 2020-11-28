cmake_minimum_required(VERSION 3.17)
project(kasa C)

set(CMAKE_C_STANDARD 99)

###################### AVR ######################
set(AVR_PROGRAMMER arduino)
set(AVR_UPLOADTOOL_PORT /dev/ttyUSB0)
set(AVR_UPLOADTOOL_BAUDRATE 57600)
set(AVR_MCU atmega1280)
set(AVR_UPLOADTOOL_VERBOSE true)

set(AVR_H_FUSE 0xC0)
set(AVR_L_FUSE 0x40)

set(MCU_SPEED "16000000UL")

include(./avr-gcc.cmake)

avr_generate_fixed_targets()

add_definitions("-DF_CPU=${MCU_SPEED}")
add_definitions("-fpack-struct")
add_definitions("-fshort-enums")
add_definitions("-Wall")
add_definitions("-funsigned-char")
add_definitions("-funsigned-bitfields")
add_definitions("-ffunction-sections")
add_definitions("-c")
add_definitions("-std=gnu99")
add_definitions("-Os")

if(DEFINED ENV{AVR_FIND_ROOT_PATH})
    set(CMAKE_FIND_ROOT_PATH $ENV{AVR_FIND_ROOT_PATH})
else(DEFINED ENV{AVR_FIND_ROOT_PATH})
    if(EXISTS "/opt/local/avr")
        set(CMAKE_FIND_ROOT_PATH "/opt/local/avr")
    elseif(EXISTS "/usr/avr")
        set(CMAKE_FIND_ROOT_PATH "/usr/avr")
    elseif(EXISTS "/usr/lib/avr")
        set(CMAKE_FIND_ROOT_PATH "/usr/lib/avr")
    elseif(EXISTS "/usr/local/CrossPack-AVR")
        set(CMAKE_FIND_ROOT_PATH "/usr/local/CrossPack-AVR")
    else(EXISTS "/opt/local/avr")
        message(FATAL_ERROR "Please set AVR_FIND_ROOT_PATH in your environment.")
    endif(EXISTS "/opt/local/avr")
endif(DEFINED ENV{AVR_FIND_ROOT_PATH})
set(CMAKE_SYSTEM_INCLUDE_PATH "${CMAKE_FIND_ROOT_PATH}/include")
set(CMAKE_SYSTEM_LIBRARY_PATH "${CMAKE_FIND_ROOT_PATH}/lib")

message(STATUS "Set CMAKE_FIND_ROOT_PATH to ${CMAKE_FIND_ROOT_PATH}")
message(STATUS "Set CMAKE_SYSTEM_INCLUDE_PATH to ${CMAKE_SYSTEM_INCLUDE_PATH}")
message(STATUS "Set CMAKE_SYSTEM_LIBRARY_PATH to ${CMAKE_SYSTEM_LIBRARY_PATH}")

include_directories(${CMAKE_SYSTEM_INCLUDE_PATH} ${CMAKE_SYSTEM_LIBRARY_PATH})

###################### FreeRTOS ######################

include(./lib/freeRTOS9xx/freeRTOSFilePaths.cmake)

add_avr_library(FreeRTOS STATIC ${FreeRTOS_SOURCES})
target_include_directories(FreeRTOS PUBLIC ${FreeRTOS_INCLUDE_PUBLIC_DIRS})

add_definitions("-D_WIZCHIP_=5100")

###################### coreJSON ######################

include(./lib/coreJSON/jsonFilePaths.cmake)

add_avr_library(coreJSON STATIC ${JSON_SOURCES})
target_include_directories(coreJSON PUBLIC ${JSON_INCLUDE_PUBLIC_DIRS})

###################### Kasa ######################

file(GLOB KASA_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/src/*.c")
file(GLOB KASA_HEADERS "${CMAKE_CURRENT_SOURCE_DIR}/src/*.h" )

add_avr_executable(kasa ${KASA_HEADERS} ${KASA_SOURCES})
target_include_directories(kasa.elf PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/src")
target_link_libraries(kasa.elf FreeRTOS coreJSON)
