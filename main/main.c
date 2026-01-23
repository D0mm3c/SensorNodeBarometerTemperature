#include <stdio.h>
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "sensorhub.h"
static const char *TAG = "SensorNode";

void app_main(void)
{
    ESP_ERROR_CHECK(sensorhub_init());

    int tick = 0;

    sensorhub_sample_t sample = {0};

    while (1)
    {
        ESP_ERROR_CHECK(sensorhub_sample(&sample));
        ESP_LOGI(TAG, "tick=%d T1=%.2fC T2=%.2f C  P=%.2f hPa F=%.2f %%", tick++, sample.ds18b20_temp_c, sample.bme280_temp_c, sample.bme280_press_pa/100, sample.bme280_humid_pct);
      
        //vTaskDelay(pdMS_TO_TICKS(1000));
    }
}
