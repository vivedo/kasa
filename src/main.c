#include <stdlib.h>
#include <avr/io.h>
#include <FreeRTOS.h>
#include <task.h>
#include <time.h>
#include <serial.h>
#include "local_io.h"
#include "input_scanner.h"
#include "output_manager.h"

int main(void) {
    // INPUT PORTS
    DDRA = 0b0; // PA0~PA7
    DDRC = 0b0; // PC0~PC7

    // OUTPUT PORTS
    PORTG = 0xFF & PORTG_OUT_MASK; // pre-set input high as relays are active low
    PORTL = 0xFF & PORTL_OUT_MASK;
    PORTD = 0xFF & PORTD_OUT_MASK;
    PORTK = 0xFF & PORTK_OUT_MASK;

    DDRK |= PORTK_OUT_MASK; // PK0~PK7
    DDRG |= PORTG_OUT_MASK; // PG0~PG2
    DDRL |= PORTL_OUT_MASK; // PL4~PL7
    DDRD |= PORTD_OUT_MASK; // PD7

    xSerialPort = xSerialPortInitMinimal(USART0, 115200, portSERIAL_BUFFER_TX, portSERIAL_BUFFER_RX);
    xSerialPrint("Starting\r\n");

    start_input_scanner();
    start_output_manager();

    vTaskStartScheduler();
}