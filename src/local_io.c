//
// Created by vivedo on 26/11/20.
//

#include "local_io.h"

uint16_t read_inputs(void) {
    return ~(INPUT_REGISTER_LOW | (INPUT_REGISTER_HIGH << 8u));
}

bool read_input(uint8_t input) {
    if(input < 8)
        return ((~INPUT_REGISTER_LOW >> input) & 1u);
    else
        return ((~INPUT_REGISTER_HIGH >> (input - 8u)) & 1u);
}

void set_outputs(uint16_t outputs) {
    OUTPUT_REGISTER_LOW = ~outputs; // RELAYS ARE ACTIVE LOW
    OUTPUT_REGISTER_HIGH = ~outputs >> 8u;
}

void set_output(uint8_t output, bool state) {
    if(output < 8) {
        if (state)
            OUTPUT_REGISTER_LOW &= ~_BV(output); // RELAYS ARE ACTIVE LOW
        else
            OUTPUT_REGISTER_LOW |= _BV(output);
    } else { // no need to check output < 16, shifting values > 7 will make everything stay the same
        if (state)
            OUTPUT_REGISTER_HIGH &= ~_BV(output - 8u); // RELAYS ARE ACTIVE LOW
        else
            OUTPUT_REGISTER_HIGH |= _BV(output - 8u);
    }
}

uint16_t get_outputs() {
    return ~(OUTPUT_REGISTER_LOW | (OUTPUT_REGISTER_HIGH << 8u));
}
