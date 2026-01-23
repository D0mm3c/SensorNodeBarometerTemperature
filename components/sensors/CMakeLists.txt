idf_component_register(
    SRCS "bmp280_sensor.c" "ds18b20_sensor.c" "sensorhub.c"
    INCLUDE_DIRS "include"
    REQUIRES onewire_bus ds18b20 bmp280 i2cdev driver
)