//
// Created by vivedo on 26/11/20.
//
// This file contains bad ways to do things.
// Should they be made in a batter way? maybe.
// Do i have the time to do so? no.
//
#include <FreeRTOS.h>
#include <task.h>
#include <stdbool.h>
#include <timers.h>
#include "output_manager.h"
#include "local_io.h"

TimerHandle_t curtain_stopper_timer = NULL;
void start_curtain_stopper();
void stop_curtain_stopper();
void curtain_stopper_timer_cb(TimerHandle_t handle);

TimerHandle_t lamp0_stopper_timer = NULL;
void start_lamp0_stopper(bool long_timer);
void stop_lamp0_stopper();
uint8_t get_lamp0_stopper_status();
void lamp0_stopper_timer_cb(TimerHandle_t handle);

void toggle_devices(uint16_t toggle_mask) {
    uint16_t outputs = get_outputs();

    // SIMPLE LIGHTS
    outputs ^= toggle_mask & 0b0001111111111111;

    // SUN CURTAIN
    if(toggle_mask & (_BV(14) | _BV(15))) {
        if(toggle_mask & _BV(14)) {
            outputs &= ~_BV(14); // SET DIRECTION
        } else {
            outputs |= _BV(14); // SET DIRECTION
        }

        if(outputs & _BV(15)) {
            stop_curtain_stopper();
            outputs &= ~_BV(15); // STOP MOTOR
        } else {
            start_curtain_stopper();
            outputs |= _BV(15); // START MOTOR
        }

    }

    // LAMP0
    if(toggle_mask & _BV(13)) {
        if(outputs & _BV(13)) { // LAMP0 ACTIVE
            if(get_lamp0_stopper_status() == SHORT_PERIOD) { // SHORT TIMER, making it long
                start_lamp0_stopper(true); // start long lamp0 stopper
            } else {
                stop_lamp0_stopper();
                outputs &= ~_BV(13); // SHUT DOWN LAMP0
            }
        } else {
            start_lamp0_stopper(false); // start short lamp0 stopper
            outputs |= _BV(13); // LIGHT LAMP0
        }
    }


    set_outputs(outputs);

}

void start_curtain_stopper() {
    if(curtain_stopper_timer == NULL)
        curtain_stopper_timer = xTimerCreate("curtain_stopper", CURTAIN_DURATION * 1000 / portTICK_PERIOD_MS, pdFALSE, (void*) 0, curtain_stopper_timer_cb);

    xTimerReset(curtain_stopper_timer, 10);
}

void stop_curtain_stopper() {
    if(curtain_stopper_timer != NULL)
        xTimerStop(curtain_stopper_timer, 10);
}

void curtain_stopper_timer_cb(TimerHandle_t handle) {
    uint16_t outputs = get_outputs();
    outputs &= ~_BV(15);
    set_outputs(outputs);
}

void start_lamp0_stopper(bool long_timer) {
    if(lamp0_stopper_timer == NULL)
        lamp0_stopper_timer = xTimerCreate("lamp_stopper", LAMP0_DURATION_SHORT * 1000 / portTICK_PERIOD_MS, pdFALSE, (void*) 0, lamp0_stopper_timer_cb);

    xTimerChangePeriod(lamp0_stopper_timer, long_timer ? (LAMP0_DURATION_LONG * 1000 / portTICK_PERIOD_MS) : (LAMP0_DURATION_SHORT * 1000 / portTICK_PERIOD_MS), 10);
    xTimerReset(lamp0_stopper_timer, 10);
}

void stop_lamp0_stopper() {
    if(lamp0_stopper_timer != NULL)
        xTimerStop(lamp0_stopper_timer, 10);
}

uint8_t get_lamp0_stopper_status() {
    if(xTimerIsTimerActive(lamp0_stopper_timer) == pdFALSE)
        return STOPPED;

    if(xTimerGetPeriod(lamp0_stopper_timer) == (LAMP0_DURATION_SHORT * 1000 / portTICK_PERIOD_MS))
        return SHORT_PERIOD;

    return LONG_PERIOD;
}


void lamp0_stopper_timer_cb(TimerHandle_t handle) {
    uint16_t outputs = get_outputs();
    outputs &= ~_BV(13);
    set_outputs(outputs);
}