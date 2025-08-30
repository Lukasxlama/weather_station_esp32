// --- Include Guard --- //
#pragma once

// --- Include Directives --- //
#include <U8g2lib.h>
#include "SensorData.hpp"

// --- Classes --- //
/**
 * @brief Manager class for the OLED display.
 *
 * Handles initialization, showing messages and sensor data,
 * and power control of the display.
 */
class DisplayManager
{
    private:
        // --- Member --- //
        U8G2_SH1106_128X64_NONAME_F_HW_I2C u8g2; /** U8g2 display instance */

    public:
        // --- Constructor --- //
        /**
         * @brief Construct a new DisplayManager object.
         */
        DisplayManager();

        // --- Methods --- //
        /**
         * @brief Initialize the display. Must be called before other methods.
         *
         * @return true if initialization succeeded
         * @return false otherwise
         */
        [[nodiscard]] bool begin();

        /**
         * @brief Show a simple text message on the display.
         *
         * @param message Null-terminated string to display
         */
        void showMessage(const char* message);

        /**
         * @brief Show sensor readings on the display.
         *
         * @param sensorData Struct with sensor data to display
         */
        void showSensorReadings(const SensorData& sensorData);

        /**
         * @brief Completely clear the display (both buffer and screen).
         *
         * Useful for full resets or when switching display modes.
         */
        void clearAll();

        /**
         * @brief Put the display into power saving mode.
         */
        void deactivate();

        /**
         * @brief Reactivate the display after deactivation.
         */
        void reactivate();
};
