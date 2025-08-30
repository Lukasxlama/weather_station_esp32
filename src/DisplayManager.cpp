#include "DisplayManager.hpp"

DisplayManager::DisplayManager()
    : u8g2(U8G2_R0, /* reset=*/U8X8_PIN_NONE) {}

bool DisplayManager::begin()
{
    this->u8g2.clearDisplay();
    return this->u8g2.begin();
}

void DisplayManager::showMessage(const char* message)
{
    this->u8g2.clearBuffer();
    this->u8g2.setFont(u8g2_font_6x10_tr);
    this->u8g2.drawStr(0, 20, message);
    this->u8g2.sendBuffer();
}

void DisplayManager::showSensorReadings(const SensorData& sensorData)
{
    char buf[32];
    this->u8g2.clearBuffer();
    this->u8g2.setFont(u8g2_font_6x10_tr);

    snprintf(buf, sizeof(buf), "Temp: %.1f C", sensorData.temperature);
    this->u8g2.drawStr(0, 10, buf);

    snprintf(buf, sizeof(buf), "Hum: %.1f %%", sensorData.humidity);
    this->u8g2.drawStr(0, 22, buf);

    snprintf(buf, sizeof(buf), "Pres: %.1f hPa", sensorData.pressure);
    this->u8g2.drawStr(0, 34, buf);

    snprintf(buf, sizeof(buf), "Gas: %.1f kOhm", sensorData.gasResistance);
    this->u8g2.drawStr(0, 46, buf);

    this->u8g2.sendBuffer();
}

void DisplayManager::clearAll()
{
    this->u8g2.clearDisplay();
}

void DisplayManager::deactivate()
{
    this->u8g2.setPowerSave(1);
}

void DisplayManager::reactivate()
{
    this->u8g2.setPowerSave(0);
}