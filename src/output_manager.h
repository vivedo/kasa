//
// Created by vivedo on 26/11/20.
//

#ifndef KASA_OUTPUT_MANAGER_H
#define KASA_OUTPUT_MANAGER_H

#define CURTAIN_DURATION 25
#define LAMP0_DURATION_SHORT 5//60 * 3
#define LAMP0_DURATION_LONG 15//60 * 25

#define STOPPED 0
#define LONG_PERIOD 1
#define SHORT_PERIOD 2

void start_output_manager(void);

void toggle_devices(uint16_t toggle_mask);

#endif //KASA_OUTPUT_MANAGER_H
