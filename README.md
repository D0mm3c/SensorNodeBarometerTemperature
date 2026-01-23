# SensorNode – Barometer & Temperature

This project is part of the **SensorNode** series and focuses on building a modular sensor node based on an ESP32.
The node aggregates environmental sensor data and is designed to serve as a foundation for future telemetry
and CAN bus integration.

Currently, the SensorNode integrates a digital temperature sensor and an environmental sensor to measure
temperature, air pressure and humidity.

---

## Features

- ESP32-based sensor node
- Modular sensor architecture (sensor wrapper + sensor hub)
- Temperature measurement via **DS18B20** (1-Wire)
- Temperature, pressure and humidity measurement via **BME280** (I²C)
- Centralized sensor initialization and sampling
- Periodic logging via ESP-IDF logging facilities

---

## Sensors

### DS18B20
- Interface: 1-Wire
- Measurements:
  - Temperature (°C)

### BME280
- Interface: I²C
- Measurements:
  - Temperature (°C)
  - Air pressure (Pa / hPa)
  - Relative humidity (%)

> **Note:**  
> Some internal identifiers still reference `bmp280`.  
> This is a naming artifact and will be aligned to `bme280` in a follow-up cleanup commit.

---

### Sensor Wrappers

Each sensor is encapsulated in its own module providing:
- `init()` – hardware and driver initialization
- `read()` – retrieval of sensor data

### SensorHub

The SensorHub:
- Initializes shared infrastructure (I²C, i2cdev)
- Initializes all sensors
- Collects sensor data into a unified data structure

This separation keeps `app_main()` minimal and allows easy extension
(e.g. CAN bus, telemetry, logging backends).

---

## Example Output

tick=32 T1=23.61C T2=23.83f C  P=1003.45hPa F=51.8%

---

## Build & Flash

The project is built using **ESP-IDF**.

```bash
idf.py build
idf.py -p <PORT> flash monitor
```

## Roadmap
- Rename internal bmp280 identifiers to bme280
- CAN bus integration
- Structured telemetry frames
- Data logging on external host (e.g. Raspberry Pi)
- Additional sensor modules

## Status
### Work in Progress
The project is actively developed and serves as a learning and experimentation platform
for embedded systems, sensor integration and telemetry architectures.