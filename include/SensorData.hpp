// --- Include Guard --- //
#pragma once

// --- Include Directives --- //
#include <cstdint>

// --- Structs --- //
/**
 * @brief Struct to hold BME680 sensor data.
 */
struct SensorData
{
    float temperature;   /** Temperature in °C */
    float humidity;      /** Relative humidity in % */
    float pressure;      /** Pressure in hPa */
    float gasResistance; /** Gas resistance in kΩ */
};