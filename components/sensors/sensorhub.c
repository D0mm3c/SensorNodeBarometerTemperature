#include "sensorhub.h"

#include "esp_err.h"
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "bmp280_sensor.h"
#include "ds18b20_sensor.h"

#include "i2cdev.h"
#include "driver/i2c.h"

// DS18B20
#define DS18B20_PIN 4

// BMP280
#define BMP280_ADDRESS 0x76
#define I2C_PORT I2C_NUM_0
#define SDA_GPIO 15
#define SCL_GPIO 18
#define I2C_FREQ_HZ 100000

static const char *TAG = "sensorhub";
static bool s_inited = false;
esp_err_t sensorhub_init()
{
    if (s_inited)
        return ESP_OK;
        
    // I2C init
    ESP_ERROR_CHECK(i2cdev_init());

    // CONFIG
    //  ds18b20 config
    ds18b20_sensor_cfg_t ds18b20_cfg = {
        .gpio_num = DS18B20_PIN};

    // bmp280 config
    bmp280_sensor_cfg_t bmp280_cfg = {
        .addr = BMP280_ADDRESS,
        .port = I2C_PORT,
        .sda_gpio = SDA_GPIO,
        .scl_gpio = SCL_GPIO};

    // ds18b20 init
    ESP_ERROR_CHECK(ds18b20_sensor_init(&ds18b20_cfg));

    // bmp280 init
    ESP_ERROR_CHECK(bmp280_sensor_init(&bmp280_cfg));

    ESP_LOGI(TAG, "Everything init");

    s_inited = true;
    return ESP_OK;
}

esp_err_t sensorhub_sample(sensorhub_sample_t *sample)
{
    if (!sample)
        return ESP_ERR_INVALID_ARG;
    if (!s_inited)
        return ESP_ERR_INVALID_STATE;

    *sample = (sensorhub_sample_t){0};

    esp_err_t err = ds18b20_sensor_read_temp_c(&sample->ds18b20_temp_c);
    if (err != ESP_OK)
        return err;

    err = bmp280_sensor_get_floats(&sample->bme280_temp_c,
                                   &sample->bme280_press_pa,
                                   &sample->bme280_humid_pct);
    if (err != ESP_OK)
        return err;

    return ESP_OK;
}