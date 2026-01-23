#pragma once
#include "esp_err.h"

typedef struct 
{
    int gpio_num;
   
}ds18b20_sensor_cfg_t;

esp_err_t ds18b20_sensor_init(const ds18b20_sensor_cfg_t *cfg);
esp_err_t ds18b20_sensor_read_temp_c(float *out_temp_c);

/*
______  _____ __   _____ ______  _____  _____ 
|  _  \/  ___/  | |  _  || ___ \/ __  \|  _  |
| | | |\ `--.`| |  \ V / | |_/ /`' / /'| |/' |
| | | | `--. \| |  / _ \ | ___ \  / /  |  /| |
| |/ / /\__/ /| |_| |_| || |_/ /./ /___\ |_/ /
|___/  \____/\___/\_____/\____/ \_____/ \___/ 
                                              
*/                                            
                                              
                                              
                                              
                                              
                                              
                                              
                                              
                                              