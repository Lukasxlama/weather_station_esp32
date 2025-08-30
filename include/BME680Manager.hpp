// --- Include Guard --- //
#pragma once

// --- Include Directives --- //
#include <Adafruit_BME680.h>
#include "SensorData.hpp"

// --- Classes --- //
/**
 * @brief Manager class for the BME680 sensor.
 *
 * Handles initialization, configuration, and reading of sensor data.
 */
class BME680Manager
{
    private:
        // --- Member --- //
        Adafruit_BME680 bme;               /** BME680 sensor instance */
        uint8_t         tempOversampling;  /** Temperature oversampling setting */
        uint8_t         humOversampling;   /** Humidity oversampling setting */
        uint8_t         pressOversampling; /** Pressure oversampling setting */
        uint16_t        gasHeaterTemp;     /** Gas heater temperature in °C */
        uint16_t        gasHeaterDur;      /** Gas heater duration in ms */

    public:
        // --- Constructor --- //
        /**
         * @brief Construct a new BME680Manager object with oversampling and heater settings.
         *
         * @param tempOS Temperature oversampling (e.g., 1, 2, 4, 8, 16)
         * @param humOS Humidity oversampling
         * @param pressOS Pressure oversampling
         * @param gasTemp Gas heater temperature in °C
         * @param gasDur Gas heater duration in milliseconds
         */
        explicit BME680Manager(uint8_t tempOS, uint8_t humOS, uint8_t pressOS, uint16_t gasTemp, uint16_t gasDur);

        // --- Methods --- //
        /**
         * @brief Initialize the BME680 sensor with the configured settings.
         *
         * @return true if sensor initialization succeeded
         * @return false if sensor initialization failed
         */
        [[nodiscard]] bool begin();

        /**
         * @brief Trigger a sensor reading and update internal values.
         *
         * The sensor performs a forced measurement and then automatically
         * returns to sleep mode, minimizing power consumption.
         * 
         * Must be called before accessing sensor data getters.
         *
         * @return true if reading succeeded
         * @return false if reading failed
         */
        [[nodiscard]] bool performReading();

        /**
         * @brief Get the last measured temperature value.
         *
         * @return float Temperature in °C
         */
        [[nodiscard]] float getTemperature() const;

        /**
         * @brief Get the last measured humidity value.
         *
         * @return float Relative humidity in %
         */
        [[nodiscard]] float getHumidity() const;

        /**
         * @brief Get the last measured pressure value.
         *
         * @return float Pressure in hPa
         */
        [[nodiscard]] float getPressure() const;

        /**
         * @brief Get the last measured gas resistance.
         *
         * @return uint32_t Gas resistance in kΩ
         */
        [[nodiscard]] float getGasResistance() const;

        /**
         * @brief Get all sensor values as a single struct.
         *
         * @return SensorData Struct containing temperature, humidity, pressure and gas resistance.
         */
        [[nodiscard]] SensorData getSensorData() const;
};