//
// Created by vivedo on 26/11/20.
//
#include <FreeRTOS.h>
#include <task.h>
#include <buttonDebounce.h>

#include "local_io.h"
#include "input_scanner.h"
#include "output_manager.h"
#include "common.h"

TaskHandle_t input_scanner_handle = NULL;
debouncer debouncerA;
debouncer debouncerB;

_Noreturn static void input_scanner_task(void *pvParameters);

void start_input_scanner(void) {
    buttonDebounceInit(&debouncerA, 0x00);
    buttonDebounceInit(&debouncerB, 0x00);

    xTaskCreate(input_scanner_task, (const char *) "input_scanner", 1024, NULL, 3, &input_scanner_handle);
}

_Noreturn static void input_scanner_task(void *pvParameters) {
    for(ever) {
        uint16_t read = read_inputs();

        buttonProcess(&debouncerA, read);
        buttonProcess(&debouncerB, read >> 8u);

        uint16_t toggle_mask = buttonPressed(&debouncerA, 0xff) | (buttonPressed(&debouncerB, 0xff) << 8u);

        if(toggle_mask)
            toggle_devices(toggle_mask);

        vTaskDelay(5 / portTICK_PERIOD_MS);
    }
}