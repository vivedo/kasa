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
add_definitions("-D_WIZCHIP_=5100")
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

set(FreeRTOS9xx_include_dir "${CMAKE_CURRENT_SOURCE_DIR}/lib/freeRTOS9xx/include")
file(GLOB_RECURSE FreeRTOS9xx_headers "${FreeRTOS9xx_include_dir}/*.h")

set(FreeRTOS9xx_source_dir "${CMAKE_CURRENT_SOURCE_DIR}/lib/freeRTOS9xx")
file(GLOB FreeRTOS9xx_root_sources "${FreeRTOS9xx_source_dir}/*.c")
file(GLOB_RECURSE FreeRTOS9xx_libs
        "${FreeRTOS9xx_source_dir}/lib*/*.c"
        "${FreeRTOS9xx_source_dir}/portable/*.c"
        "${FreeRTOS9xx_source_dir}/MemMang/heap_4.c")
set(FreeRTOS9xx_sources ${FreeRTOS9xx_libs} ${FreeRTOS9xx_root_sources})

add_avr_library(FreeRTOS9xx STATIC ${FreeRTOS9xx_sources})
target_include_directories(FreeRTOS9xx PUBLIC ${FreeRTOS9xx_include_dir})

###################### Kasa ######################

file(GLOB kasa_sources "${CMAKE_CURRENT_SOURCE_DIR}/src/*.c")
file(GLOB kasa_headers "${CMAKE_CURRENT_SOURCE_DIR}/src/*.h" )
message(STATUS ${kasa_sources})
message(STATUS ${kasa_headers})

add_avr_executable(kasa ${kasa_headers} ${kasa_sources})
target_include_directories(kasa.elf PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/src")
target_link_libraries(kasa.elf FreeRTOS9xx)
