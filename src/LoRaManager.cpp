#include "LoRaManager.hpp"

LoRaManager::LoRaManager(int csPin, int resetPin, int irqPin, long frequency)
    : csPin(csPin), resetPin(resetPin), irqPin(irqPin), frequency(frequency) {}

bool LoRaManager::begin()
{
    LoRa.setPins(csPin, resetPin, irqPin);
    Serial.print("Init LoRa on ");
    Serial.print(frequency);
    Serial.println(" Hz...");
    if (!LoRa.begin(frequency))
    {
        Serial.println("Failed to initialize LoRa!");
        return false;
    }
    Serial.println("LoRa initialized successfully.");
    return true;
}

bool LoRaManager::sendMessage(const char* message)
{
    if (strlen(message) == 0)
    {
        return false;
    }

    if (LoRa.beginPacket() == 0)
    {
        return false;
    }

    LoRa.print(message);
    return LoRa.endPacket() == 1;
}

bool LoRaManager::sendSensorReadings(SensorData sensorData)
{
    char buffer[256];

    snprintf(buffer, sizeof(buffer),
             "{\"temperature\":%.1f,\"humidity\":%.1f,\"pressure\":%.1f,\"gas_resistance\":%.1f,\"timestamp\":%lu}",
             sensorData.temperature,
             sensorData.humidity,
             sensorData.pressure,
             sensorData.gasResistance,
             millis());

    return this->sendMessage(buffer);
}