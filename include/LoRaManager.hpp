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

        /**
         * @brief Send a raw message string via LoRa.
         *
         * Attempts to send the provided null-terminated message.
         *
         * @param msg The message string to send.
         *
         * @return true if the message was successfully queued and transmitted
         * @return false if sending failed (e.g. empty message or LoRa not ready)
         */
        bool sendMessage(const char* msg);

        /**
         * @brief Send formatted sensor readings as a JSON string via LoRa.
         *
         * Converts the given SensorData struct into a JSON payload and transmits it.
         *
         * @param sensorData The sensor readings to encode and send.
         *
         * @return true if the message was successfully transmitted
         * @return false if transmission failed
         */
        bool sendSensorReadings(SensorData sensorData);
};
