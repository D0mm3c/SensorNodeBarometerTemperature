#include "ds18b20_sensor.h"

#include "esp_log.h"
#include "onewire_bus.h"
#include "ds18b20.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

static const char *TAG = "ds18b20_sensor";

// internal module state
static onewire_bus_handle_t s_bus = NULL;
static ds18b20_device_handle_t s_sensor = NULL;
static bool s_inited = false;

esp_err_t ds18b20_sensor_init(const ds18b20_sensor_cfg_t *cfg)
{
    if (!cfg)
        return ESP_ERR_INVALID_ARG;
    if (s_inited)
        return ESP_OK;

    // install 1 wire bus
    onewire_bus_config_t bus_config = {
        .bus_gpio_num = cfg->gpio_num,
        .flags = {
            .en_pull_up = true, // backup, extern 4.7k resistor
        }};

    onewire_bus_rmt_config_t rmt_config = {
        .max_rx_bytes = 10, // 1byte ROM command + 8 byte ROM number + 1byte device commmand
    };

    esp_err_t err = onewire_new_bus_rmt(&bus_config, &rmt_config, &s_bus);
    if (err != ESP_OK)
        return err;

    // find device on bus
    // create 1-wire device iterator
    onewire_device_iter_handle_t iter = NULL;
    err = onewire_new_device_iter(s_bus, &iter);
    if (err != ESP_OK)
        return err;

    // get first 1 wire device
    onewire_device_t dev;
    err = onewire_device_iter_get_next(iter, &dev);
    onewire_del_device_iter(iter);

    if (err != ESP_OK)
    {
        ESP_LOGE(TAG, "No 1-Wire Device found. Check Wiring");
        return err;
    }

    // upgrade to ds18b20
    ds18b20_config_t ds_cfg = {};
    err = ds18b20_new_device_from_enumeration(&dev, &ds_cfg, &s_sensor);

    if (err != ESP_OK)
    {
        ESP_LOGE(TAG, "Found 1-Wire Device but it is not a DS18B20.");
        return err;
    }

    onewire_device_address_t addr;
    ds18b20_get_device_address(s_sensor, &addr);
    ESP_LOGI(TAG, "DS18B20 bound, addr = %016llX", addr);

    s_inited = true;
    return ESP_OK;
}

esp_err_t ds18b20_sensor_read_temp_c(float *out_temp_c)
{
    if (!out_temp_c)
        return ESP_ERR_INVALID_ARG;
    if (!s_inited || !s_bus || !s_sensor)
        return ESP_ERR_INVALID_STATE;

    // trigger conversion for all devices on the bus (only for single sensor)
    esp_err_t err = ds18b20_trigger_temperature_conversion_for_all(s_bus);
    if (err != ESP_OK)
        return err;

    
    vTaskDelay(pdMS_TO_TICKS(800));
    return ds18b20_get_temperature(s_sensor, out_temp_c);
}