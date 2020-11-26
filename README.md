# KASA
Domotic system based AVR ATmega1280 running FreeRTOS 9.

Currently based on an old Arduino Mega 1280 clone board and a W5100 shield clone

Built and burnt with cmake.
Configured for older Arduino bootloader (57600 baud), avrdude settings available in CMakeList.txt

### Software capabilities
 - Timed outputs
 - Constraint outputs (for motorized shutters/curtains)
 - MQTT control _(unimplemented)_

### Current hardware
 - Arduino Mega 1280
 - Wiznet W5100 (Arduino Ethernet shield)
 - 8x 230V/5V optocoupler board (x2)
 - 16x 5V coil, 230V10A relay board 
 - 5V2A PSU
 - DIN rail electrical box and custom 3D printed DIN headers
 
#### Future improvements
 - Custom PCB
 
#### Credits
[feilipu's](https://github.com/felipu) FreeRTOS port [avrfreertos](https://github.com/feilipu/avrfreertos)