#pragma once
#include "esp_err.h"
#include "i2cdev.h"
typedef struct 
{
   uint8_t addr;
   i2c_port_t port;
   gpio_num_t sda_gpio;
   gpio_num_t scl_gpio;
}bmp280_sensor_cfg_t;

esp_err_t bmp280_sensor_init(const bmp280_sensor_cfg_t *cfg);
esp_err_t bmp280_sensor_get_floats(float *out_temp_c, float *out_press, float *out_humid);



/* _                      _____  _____ _____ 
| |                    / __  \|  _  |  _  |
| |__  _ __ ___  _ __  `' / /' \ V /| |/' |
| '_ \| '_ ` _ \| '_ \   / /   / _ \|  /| |
| |_) | | | | | | |_) |./ /___| |_| \ |_/ /
|_.__/|_| |_| |_| .__/ \_____/\_____/\___/ 
                | |                        
                |_|                        
*/