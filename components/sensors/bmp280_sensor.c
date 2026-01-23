#include "bmp280_sensor.h"

#include "bmp280.h"
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/i2c.h"
#include "i2cdev.h"

static const char *TAG = "bmp280_sensor";

// internal module state
static bmp280_t s_bmp = {0};
static bool s_inited = false;

/*
static void i2c_master_init(void)
{
    i2c_config_t conf = {
        .mode = I2C_MODE_MASTER,
        .sda_io_num = SDA_GPIO,
        .scl_io_num = SCL_GPIO,
        .sda_pullup_en = GPIO_PULLUP_ENABLE, // ok even if module already has pullups
        .scl_pullup_en = GPIO_PULLUP_ENABLE,
        .master.clk_speed = I2C_FREQ_HZ,
        .clk_flags = 0,
    };
    ESP_ERROR_CHECK(i2c_param_config(I2C_PORT, &conf));
    ESP_ERROR_CHECK(i2c_driver_install(I2C_PORT, conf.mode, 0, 0, 0));
}
*/

esp_err_t bmp280_sensor_init(const bmp280_sensor_cfg_t *cfg)
{
    if (!cfg)
        return ESP_ERR_INVALID_ARG;
    if (s_inited)
        return ESP_OK;

    bmp280_params_t params;
    bmp280_init_default_params(&params);

    esp_err_t err = bmp280_init_desc(&s_bmp, cfg->addr, cfg->port, cfg->sda_gpio, cfg->scl_gpio);
    if (err != ESP_OK)
        return err;

    err = bmp280_init(&s_bmp, &params);
    if (err != ESP_OK)
        return err;

    ESP_LOGI(TAG, "BME280 init OK");

    s_inited = true;
    return ESP_OK;
}

esp_err_t bmp280_sensor_get_floats(float *out_temp_c, float *out_press, float *out_humid)
{
    if (!s_inited) return ESP_ERR_INVALID_STATE;
    if (!out_temp_c || !out_press || !out_humid) return ESP_ERR_INVALID_ARG;

    return bmp280_read_float(&s_bmp, out_temp_c, out_press, out_humid);
}

