// --- Include Guard --- //
#pragma once

// --- Include Directives --- //
#include <LoRa.h>
#include "SensorData.hpp"

// --- Classes --- //
/**
 * @brief Manager class for LoRa communication.
 *
 * Handles initialization and message transmission using the LoRa module.
 */
class LoRaManager
{
    private:
        // --- Member --- //
        const int    csPin;     /** Chip select pin */
        const int    resetPin;  /** Reset pin */
        const int    irqPin;    /** Interrupt pin */
        const double frequency; /** LoRa frequency in Hz */

    public:
        // --- Constructor --- //
        /**
         * @brief Construct a new LoRaManager object with configuration pins and frequency.
         *
         * @param csPin Chip select pin
         * @param resetPin Reset pin
         * @param irqPin Interrupt pin
         * @param frequency LoRa frequency in Hz
         */
        LoRaManager(int csPin, int resetPin, int irqPin, long frequency);

        // --- Methods --- //
        /**
         * @brief Initialize LoRa module with provided settings.
         *
         * @return true if initialization succeeded
         * @return false if initialization failed
         */
        [[nodiscard]] bool begin();


        bool sendMessage(const char* msg);

        bool sendSensorReadings(SensorData sensorData);
};
