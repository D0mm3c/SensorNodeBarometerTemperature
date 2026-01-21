#include <stdio.h>
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "ds18b20.h"
#include "onewire_bus.h"

#define DS18B20_PIN 4
#define MAX_DS18B20 1


static const char *TAG = "SensorNode";

void app_main(void)
{
    //install 1 wire bus
    onewire_bus_handle_t bus = NULL;
    onewire_bus_config_t bus_config = {
        .bus_gpio_num = DS18B20_PIN,
        .flags = {
            .en_pull_up = true, //backup, extern 4.7k resistor 
        }
    };

    onewire_bus_rmt_config_t rmt_config = {
        .max_rx_bytes = 10, // 1byte ROM command + 8 byte ROM number + 1byte device commmand
    };

    ESP_ERROR_CHECK(onewire_new_bus_rmt(&bus_config, &rmt_config, &bus));
    ESP_LOGI(TAG, "1-Wire Bus installed on GPIO%d", DS18B20_PIN);

    // create 1-wire device iterator
    onewire_device_iter_handle_t iter = NULL;
    ESP_ERROR_CHECK(onewire_new_device_iter(bus, &iter));
    ESP_LOGI(TAG, "Searching for 1-wire device...");

    //get first 1 wire device
    onewire_device_t dev;
    esp_err_t res = onewire_device_iter_get_next(iter, &dev);
    ESP_ERROR_CHECK(onewire_del_device_iter(iter));

    if(res != ESP_OK){
        ESP_LOGE(TAG, "No 1-Wire Device founf (res=%s). Check Wiring", esp_err_to_name(res));
        for(;;); //Lock Device
    }

    //upgrade to ds18b20
    ds18b20_device_handle_t ds18b20_1 = NULL;
    ds18b20_config_t ds_cfg = {};

    res = ds18b20_new_device_from_enumeration(&dev, &ds_cfg, &ds18b20_1);
    if(res != ESP_OK){
        ESP_LOGE(TAG, "Found 1-Wire Device but it is not a DS18B20 (res=%s).", esp_err_to_name(res));
        for(;;); //Lock Device  
    }

    onewire_device_address_t address;
    ESP_ERROR_CHECK(ds18b20_get_device_address(ds18b20_1, &address));
    ESP_LOGI(TAG, "DS18B20 found, address: %016llX", address);

    float temperature = 0.0f;
    while (1)
    {
        vTaskDelay(pdMS_TO_TICKS(1000));

        ESP_ERROR_CHECK(ds18b20_trigger_temperature_conversion_for_all(bus));
        ESP_ERROR_CHECK(ds18b20_get_temperature(ds18b20_1, &temperature));
        ESP_LOGI(TAG, "Temperature: %.2f C", temperature);
    }
}
