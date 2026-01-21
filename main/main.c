#include <stdio.h>
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "ds18b20.h"

#define ds18b20_PIN 4;


static const char *TAG = "SensorNode";

void app_main(void)
{

    while (1)
    {
        ESP_LOGI(TAG, "Hello Git");
        vTaskDelay(1000);
    }
}
