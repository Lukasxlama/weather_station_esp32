// --- Includes --- //
#include <Arduino.h>
#include <Wire.h>
#include "Config.hpp"

#if DISPLAY_ACTIVE
  #include "DisplayManager.hpp"
  DisplayManager displayManager;
#endif

#if BME_ACTIVE
  #include "BME680Manager.hpp"
  BME680Manager bmeManager(BME_TEMP_OVERSAMPLING, BME_HUM_OVERSAMPLING, BME_PRESS_OVERSAMPLING, BME_GAS_HEATER_TEMP, BME_GAS_HEATER_DURATION);
#endif

#if LORA_ACTIVE
  #include "LoRaManager.hpp"
  LoRaManager loraManager(LORA_CS_PIN, LORA_RESET_PIN, LORA_IRQ_PIN, LORA_FREQUENCY);
#endif

// --- Setup --- //
void setup()
{
  Wire.begin(SDA_PIN, SCL_PIN);

  #if SERIAL_ACTIVE
    Serial.begin(SERIAL_BAUDRATE);
  #endif

  #if DISPLAY_ACTIVE
    if (!displayManager.begin())
    {
      #if SERIAL_ACTIVE
        Serial.println("[main.cpp@44] displayManager.begin() failed...");
      #endif

      #if DEEP_SLEEP_ACTIVE
        esp_deep_sleep_start();
      #else
        while (1);
      #endif
    }
  #endif

  #if BME_ACTIVE
    if (!bmeManager.begin())
    {
      #if SERIAL_ACTIVE
        Serial.println("[main.cpp@55] bmeManager.begin() failed...");
      #endif

      #if DISPLAY_ACTIVE
        displayManager.showMessage("[main.cpp@59] bmeManager.begin() failed...");
      #endif

      #if DEEP_SLEEP_ACTIVE
        esp_deep_sleep_start();
      #else
        while (1);
      #endif
    }

    if (!bmeManager.performReading())
    {
      #if SERIAL_ACTIVE
        Serial.println("[main.cpp@68] bmeManager.performReading() failed...");
      #endif
      
      #if DISPLAY_ACTIVE
        displayManager.showMessage("[main.cpp@72] bmeManager.performReading() failed...");
      #endif

      #if DEEP_SLEEP_ACTIVE
        esp_deep_sleep_start();
      #else
        while (1);
      #endif
    }
  #endif
  
  #if LORA_ACTIVE
    if (!loraManager.begin())
    {
      #if SERIAL_ACTIVE
          Serial.println("[main.cpp@83] loraManager.begin() failed...");
      #endif

      #if DISPLAY_ACTIVE
        displayManager.showMessage("[main.cpp@87] loraManager.begin() failed...");
      #endif

      #if DEEP_SLEEP_ACTIVE
        esp_deep_sleep_start();
      #else
        while (1);
      #endif
    }
  #endif

  #if BME_ACTIVE
    SensorData sensorData = bmeManager.getSensorData();

    #if SERIAL_ACTIVE
    char debug[100];
    snprintf(debug, sizeof(debug), "[main.cpp@106] Temp: %.2f °C, Hum: %.2f %%, Pres: %.2f hPa, Gas: %.2f kΩ", sensorData.temperature, sensorData.humidity, sensorData.pressure, sensorData.gasResistance);

    Serial.println(debug);
    #endif

    #if DISPLAY_ACTIVE
      displayManager.showSensorReadings(sensorData);
    #endif

    #if LORA_ACTIVE
      if (!loraManager.sendSensorReadings(sensorData))
      {
        #if SERIAL_ACTIVE
          Serial.println("[main.cpp@121] loraManager.sendSensorReadings(sensorData) failed.");
        #endif
      }
      else {Serial.println("Message sent successfully.");}
    #endif
  #endif

  #if DEEP_SLEEP_ACTIVE
    #if SERIAL_ACTIVE
      char msg[64];
      snprintf(msg, sizeof(msg), "Going to sleep in %d seconds...", DEEP_SLEEP_DELAY_SECONDS);
      Serial.println(msg);
    #endif

    delay(DEEP_SLEEP_DELAY_SECONDS * 1000);

    #if DISPLAY_ACTIVE
      displayManager.deactivate();
    #endif

    esp_sleep_enable_timer_wakeup(DEEP_SLEEP_SECONDS * 1'000'000ULL);

    #if SERIAL_ACTIVE
      Serial.flush();
    #endif

    esp_deep_sleep_start();
  #endif
}

void loop()
{
  #if !DEEP_SLEEP_ACTIVE
    #if BME_ACTIVE
      if (bmeManager.performReading())
      {
        SensorData data = bmeManager.getSensorData();

        #if DISPLAY_ACTIVE
          displayManager.showSensorReadings(data);
        #endif

        #if LORA_ACTIVE
          loraManager.sendSensorReadings(data);
        #endif
      }

      else
      {
        #if DISPLAY_ACTIVE
          displayManager.showMessage("[main.cpp@142] bmeManager.performReading() failed...");
        #endif

        #if LORA_ACTIVE
          loraManager.sendMessage("[main.cpp@146] bmeManager.performReading() failed...");
        #endif
      }
    #endif

    delay(DEEP_SLEEP_DISABLED_LOOP_INTERVAL * 1000);
  #endif
}