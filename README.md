# ESP32 Weather Station

This project implements a weather station based on the **ESP32**.  
It collects sensor data, displays it on an OLED screen, and optionally transmits it via **LoRa**.

## Features

- **BME680 Sensor**: Measures temperature, humidity, pressure, and air quality.
- **OLED Display**: Shows real-time sensor readings.
- **LoRa Communication**: Optionally transmits data packets.
- **Modular Design**: Separate classes for sensor, display, and LoRa.
- **Deep Sleep Mode**: Reduces power consumption for battery-powered setups.
## Project Structure

```text
weather_station_esp32/
├── include/               # Header files
│   ├── BME680Manager.hpp
│   ├── Config.hpp
│   ├── DisplayManager.hpp
│   ├── LoRaManager.hpp
│   └── SensorData.hpp
├── src/                   # Implementations
│   ├── BME680Manager.cpp
│   ├── DisplayManager.cpp
│   ├── LoRaManager.cpp
│   └── main.cpp           # Entry point
├── platformio.ini         # PlatformIO project configuration
└── .gitignore
```

## Requirements

- [PlatformIO](https://platformio.org/)
- ESP32 development board
- BME680 sensor
- Optional: OLED display (e.g., SSD1306)
- Optional: LoRa module (e.g., SX1276)

The required libraries are defined in `platformio.ini`.

## Installation & Usage

1. Clone or download this repository:
   ```bash
   git clone https://github.com/Lukasxlama/weather_station_esp32.git
   cd weather_station_esp32
   ```

2. Open the project with VS Code:
   - Use the **PlatformIO VS Code extension**
   - Configure board and serial port if necessary

3. Build & Upload the code to the ESP32:
   ```bash
   pio run --target upload
   ```

4. Open the serial monitor:
   ```bash
   pio device monitor
   ```

## Configuration

All configurable settings (pin definitions, display addresses, LoRa frequencies, etc.)  
are located in [```include/Config.hpp```](include/Config.hpp).

## License

MIT License – free to use for personal and commercial projects.