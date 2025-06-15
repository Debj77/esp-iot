// mqtt.c

#include <stdio.h>
#include <string.h>
#include "mqtt_client.h"
#include "esp_log.h"
#include "cJSON.h"
#include "mqtt.h"

static const char *TAG = "MQTT_RGB";
static esp_mqtt_client_handle_t client = NULL;

extern const uint8_t ca_crt_start[]      asm("_binary_ca_crt_start");
extern const uint8_t ca_crt_end[]        asm("_binary_ca_crt_end");

extern const uint8_t client_crt_start[]  asm("_binary_client_crt_start");
extern const uint8_t client_crt_end[]    asm("_binary_client_crt_end");

extern const uint8_t client_key_start[]  asm("_binary_client_key_start");
extern const uint8_t client_key_end[]    asm("_binary_client_key_end");


static void mqtt_event_handler(void *handler_args, esp_event_base_t base, int32_t event_id, void *event_data) {
    esp_mqtt_event_handle_t event = event_data;

    switch (event->event_id) {
        case MQTT_EVENT_CONNECTED:
            ESP_LOGI(TAG, "MQTT connected");
            esp_mqtt_client_subscribe(client, "esp32/rgb", 0);
            break;

        case MQTT_EVENT_DATA: {
            // ESP_LOGI(TAG, "Topic: %.*s", event->topic_len, event->topic);
            // ESP_LOGI(TAG, "Data: %.*s", event->data_len, event->data);

            // char *json_str = strndup(event->data, event->data_len);
            // cJSON *root = cJSON_Parse(json_str);

            // if (root) {
            //     cJSON *r_item = cJSON_GetObjectItem(root, "r1");
            //     cJSON *g_item = cJSON_GetObjectItem(root, "g1");
            //     cJSON *b_item = cJSON_GetObjectItem(root, "b1");
                
            //     extern void led_rgb_set_color(uint8_t r, uint8_t g, uint8_t b);
            //     if (r_item && g_item && b_item) {
            //         int r = r_item->valueint;
            //         int g = g_item->valueint;
            //         int b = b_item->valueint;
            //         led_rgb_set_color(r, g, b);
            //         ESP_LOGI(TAG, "Received RGB: R=%d, G=%d, B=%d", r, g, b);
            //     }
            //     cJSON_Delete(root);
            // } else {
            //     ESP_LOGE(TAG, "Failed to parse JSON");
            // }

            // free(json_str);
            // break;
        }

        default:
            break;
    }
}

void mqtt_app_start(void) {
    const esp_mqtt_client_config_t mqtt_cfg = {
        .broker.address.uri = "mqtts://192.168.1.195:8883",
        // .broker.address.port = (int)1883
        //.broker.address.transport = MQTT_TRANSPORT_OVER_TCP
        // .broker.verification.certificate = (const char *)ca_cert_pem,
        // .broker.verification.certificate = 
        //  .cert_pem = (const char *)broker_cert_pem_start, // same embedding as above
        .broker.verification.certificate = (const char *)ca_crt_start,
        .credentials.authentication.certificate = (const char *)client_crt_start,
        .credentials.authentication.key = (const char *)client_key_start,
        
    };

    client = esp_mqtt_client_init(&mqtt_cfg);
    esp_mqtt_client_register_event(client, ESP_EVENT_ANY_ID, mqtt_event_handler, NULL);
    esp_mqtt_client_start(client);
}
