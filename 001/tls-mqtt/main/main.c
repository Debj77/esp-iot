// main.c
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "wifi.h"
// #include "led.h"
#include "mqtt.h"
// #include "led_rgb.h"

void app_main(void) {
    wifi_init_sta();
    // led_status_init();         // Init LED first
    // led_status_set_waiting();  // Start with blinking


    while (!wifi_is_connected()) {
        printf("Waiting for Wi-Fi...\n");
        vTaskDelay(pdMS_TO_TICKS(1000));
    }

    printf("Wi-Fi Connected! You can proceed with other tasks.\n");
    // led_status_set_connected();  // Switch to breathing when connected

    mqtt_app_start();
    // led_rgb_init();
    while (1) {
        vTaskDelay(pdMS_TO_TICKS(5000));
    }
}
