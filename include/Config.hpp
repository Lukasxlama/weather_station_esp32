/*
Config.hpp
Compile-time feature flags and pin configuration
Values can be deactivated for memory optimization
*/

// --- Include Guard --- //
#pragma once

// --- PINs --- //
inline constexpr int SDA_PIN = 21;
inline constexpr int SCL_PIN = 22;

// --- Deep Sleep Values --- //
#define DEEP_SLEEP_ACTIVE 1

#if DEEP_SLEEP_ACTIVE
    inline constexpr int DEEP_SLEEP_SECONDS = 60;
    inline constexpr int DEEP_SLEEP_DELAY_SECONDS = 5;
#else
    inline constexpr int DEEP_SLEEP_DISABLED_LOOP_INTERVAL = 5;
#endif

// --- Serial Values --- //
#define SERIAL_ACTIVE 0

#if SERIAL_ACTIVE
    inline constexpr unsigned long SERIAL_BAUDRATE = 115200;
#endif

// --- Display Values --- //
#define DISPLAY_ACTIVE 1

// --- BME Values --- //
#define BME_ACTIVE 1

#if BME_ACTIVE
    inline constexpr uint8_t BME_TEMP_OVERSAMPLING = 4;
    inline constexpr uint8_t BME_HUM_OVERSAMPLING = 2;
    inline constexpr uint8_t BME_PRESS_OVERSAMPLING = 3;
    inline constexpr uint16_t BME_GAS_HEATER_TEMP = 320;
    inline constexpr uint16_t BME_GAS_HEATER_DURATION = 150;
#endif

// --- LoRa Values --- //
#define LORA_ACTIVE 1

#if LORA_ACTIVE
    inline constexpr int LORA_CS_PIN = 5;
    inline constexpr int LORA_RESET_PIN = 14;
    inline constexpr int LORA_IRQ_PIN = 2;
    inline constexpr long LORA_FREQUENCY = 868000000L;
#endif
