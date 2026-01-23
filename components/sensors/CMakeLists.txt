idf_component_register(
    SRCS "ds18b20_sensor.c"
    INCLUDE_DIRS "include"
    REQUIRES onewire_bus ds18b20
)