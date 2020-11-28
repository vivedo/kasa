//
// Created by vivedo on 26/11/20.
//
#include <FreeRTOS.h>
#include <task.h>
#include <spi.h>
#include <diskio.h>
#include <serial.h>
#include <inet.h>
#include <time.h>
#include "web.h"
#include "common.h"

TaskHandle_t dhcp_handle;

_Noreturn static void dhcp_task(void *pvParameters);

void start_web_iface(void) {
    xTaskCreate(dhcp_task, (const char *) "dhcp", 256, NULL, 1, &dhcp_handle);
}

_Noreturn void dhcp_task(void *pvParameters) {
    TickType_t xLastWakeTime;

    xLastWakeTime = xTaskGetTickCount();

    spiBegin(Wiznet);

#if 0 // currently disable SD card
    if (disk_status(0) == STA_NOINIT)
        if (disk_initialize(0))
            if (disk_initialize(0))
                xSerialPrint_P(PSTR("\r\nSDCard initialisation failed..!\r\nPlease power cycle the SDCard.\r\nCheck write protect.\r\n"));
#endif

    init_DHCP_client(DHCP_PREFERRED_SOCKET, 0, 0);

    while (!getIP_DHCPS())
        xSerialPrint_P(PSTR("\r\ngetIP_DHCPS waiting!\r\n"));

    //vTaskResume( xTaskWebServer );

    init_NTP(NTP_PREFERRED_SOCKET);
    set_zone(+1 * ONE_HOUR); // set the TZ (GMT+1)
    check_NTP(get_NTP_socket());

    // Maintain DHCP IP assignment
    for (ever) {
        check_DHCP_state(get_DHCP_socket());

        if ((time(NULL) - get_NTP_reference_time()) > NTP_REFRESH_PERIOD)
            check_NTP(get_NTP_socket());

        time_t rawtime;
        time(&rawtime);
        struct tm *timeinfo = localtime(&rawtime);

        char formatDateBuffer[80];
        strftime(formatDateBuffer, sizeof(formatDateBuffer), "%d-%m-%Y %H:%M:%S", timeinfo);
        xSerialPrintf("\r\ntime %s\r\n", formatDateBuffer);

        vTaskDelayUntil(&xLastWakeTime, (30000 / portTICK_PERIOD_MS)); // 30 seconds
    }

}
