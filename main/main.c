#include <stdio.h>
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "ds18b20_sensor.h"

#define DS18B20_PIN 4
#define MAX_DS18B20 1

static const char *TAG = "SensorNode";

void app_main(void)
{
    // ds18b20 config
    ds18b20_sensor_cfg_t cfg = {
        .gpio_num = 4};

    // ds18b20 init
    ESP_ERROR_CHECK(ds18b20_sensor_init(&cfg));
    int tick = 0;

    while (1)
    {
        float temperatur = 0.0f;
        if(ds18b20_sensor_read_temp_c(&temperatur) == ESP_OK){
            ESP_LOGI(TAG, "tick=%d temp=%.2fC", tick++, temperatur);
        }else{
            ESP_LOGI(TAG, "tick=%d temp read failed", tick++);
        }
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}
