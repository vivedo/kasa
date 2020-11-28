#include <stdlib.h>
#include <avr/io.h>
#include <FreeRTOS.h>
#include <task.h>
#include <time.h>
#include <serial.h>
#include "local_io.h"
#include "input_scanner.h"
#include "output_manager.h"
#include "web.h"

// Ethernet MAC addr
uint8_t src_mac_addr[6] = {0x00, 0x08, 0xDC, 0x00, 0xCA, 0xFE};

int main(void) {
    // INPUT PORTS
    DDRA = 0b0; // PA0~PA7
    DDRC = 0b0; // PC0~PC7

    // OUTPUT PORTS
    PORTL = 0xFF;// pre-set input high as relays are active low
    PORTK = 0xFF;

    DDRK |= 0xFF; // PK0~PK7
    DDRL |= 0xFF; // PL0~PL7

    xSerialPort = xSerialPortInitMinimal(USART0, 115200, portSERIAL_BUFFER_TX, portSERIAL_BUFFER_RX);
    xSerialPrint("Starting\r\n");

    start_input_scanner();
    start_web_iface();

    vTaskStartScheduler();
}