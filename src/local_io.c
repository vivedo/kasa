//
// Created by vivedo on 26/11/20.
//

#include "local_io.h"

uint16_t outputs_state = 0;

uint16_t read_inputs(void) {
    return ~(PINA | (PINC << 8));
}

bool read_input(uint8_t input) {
    if(input < 8)
        return ~((PINA >> input) & 1u);
    else
        return ~((PINC >> (input - 8u)) & 1u);
}

void set_outputs(uint16_t outputs) {
    outputs_state = outputs;
    outputs = ~outputs;
    PORTK = outputs & 0xFF;

    if((outputs >> 8u) & 1u) PORTG |= _BV(PG2);
    else PORTG &= ~_BV(PG2);

    if((outputs >> 9u) & 1u) PORTD |= _BV(PD7);
    else PORTD &= ~_BV(PD7);

    if((outputs >> 10u) & 1u) PORTG |= _BV(PG0);
    else PORTG &= ~_BV(PG0);

    if((outputs >> 11u) & 1u) PORTG |= _BV(PG1);
    else PORTG &= ~_BV(PG1);

    if((outputs >> 12u) & 1u) PORTL |= _BV(PL6);
    else PORTL &= ~_BV(PL6);

    if((outputs >> 13u) & 1u) PORTL |= _BV(PL7);
    else PORTL &= ~_BV(PL7);

    if((outputs >> 14u) & 1u) PORTL |= _BV(PL4);
    else PORTL &= ~_BV(PL4);

    if((outputs >> 15u) & 1u) PORTL |= _BV(PL5);
    else PORTL &= ~_BV(PL5);
}

void set_output(uint8_t output, bool state) {
    if(output < 8) {
        if(state)
            PORTK |= _BV(output);
        else
            PORTK &= ~_BV(output);
    } else {
        // TODO: implement
    }
}

uint16_t get_outputs() {
    return outputs_state;
};
