//
// Created by vivedo on 26/11/20.
//

#ifndef KASA_LOCAL_IO_H
#define KASA_LOCAL_IO_H

#include <stdbool.h>
#include <avr/io.h>

#define PORTG_OUT_MASK 0b00000111
#define PORTL_OUT_MASK 0b11110000
#define PORTD_OUT_MASK 0b10000000
#define PORTK_OUT_MASK 0b11111111

uint16_t read_inputs(void);
bool read_input(uint8_t input);
void set_outputs(uint16_t outputs);
void set_output(uint8_t output, bool state);
uint16_t get_outputs();

#endif //KASA_LOCAL_IO_H
