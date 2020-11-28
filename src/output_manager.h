//
// Created by vivedo on 26/11/20.
//

#ifndef KASA_OUTPUT_MANAGER_H
#define KASA_OUTPUT_MANAGER_H

#define CURTAIN_DURATION 25u
#define LAMP0_DURATION_SHORT 60u * 3
#define LAMP0_DURATION_LONG 60u * 25

#define STOPPED 0u
#define LONG_PERIOD 1u
#define SHORT_PERIOD 2u

void toggle_devices(uint16_t toggle_mask);

#endif //KASA_OUTPUT_MANAGER_H
