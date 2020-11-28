//
// Created by vivedo on 26/11/20.
//

#ifndef KASA_LOCAL_IO_H
#define KASA_LOCAL_IO_H

#include <stdbool.h>
#include <avr/io.h>

#define OUTPUT_REGISTER_LOW  PORTK
#define OUTPUT_REGISTER_HIGH PORTL
#define INPUT_REGISTER_LOW   PINA
#define INPUT_REGISTER_HIGH  PINC

uint16_t read_inputs(void);
bool read_input(uint8_t input);
void set_outputs(uint16_t outputs);
void set_output(uint8_t output, bool state);
uint16_t get_outputs();

#endif //KASA_LOCAL_IO_H
