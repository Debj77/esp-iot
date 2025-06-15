// wifi.h
#pragma once

#include "esp_event.h"
#include "esp_wifi.h"
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/event_groups.h"

// Wi-Fi credentials
#define WIFI_SSID "DEBJYOTI-WIFI"
#define WIFI_PASS "debjyoti@321"

// Bit flags
#define WIFI_CONNECTED_BIT BIT0

void wifi_init_sta(void);
bool wifi_is_connected(void);

