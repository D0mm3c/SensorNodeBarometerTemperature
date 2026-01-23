#pragma once
#include "esp_err.h"

typedef struct {
    float ds18b20_temp_c;
    float bme280_temp_c;
    float bme280_press_pa;
    float bme280_humid_pct;
} sensorhub_sample_t;

esp_err_t sensorhub_init(void);
esp_err_t sensorhub_sample(sensorhub_sample_t *sample);

/*
 _____                           _           _     
/  ___|                         | |         | |    
\ `--.  ___ _ __  ___  ___  _ __| |__  _   _| |__  
 `--. \/ _ \ '_ \/ __|/ _ \| '__| '_ \| | | | '_ \ 
/\__/ /  __/ | | \__ \ (_) | |  | | | | |_| | |_) |
\____/ \___|_| |_|___/\___/|_|  |_| |_|\__,_|_.__/ 
                                        
*/