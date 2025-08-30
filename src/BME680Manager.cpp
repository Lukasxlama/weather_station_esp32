#include "BME680Manager.hpp"

BME680Manager::BME680Manager(uint8_t tempOS, uint8_t humOS, uint8_t pressOS, uint16_t gasTemp, uint16_t gasDur)
    : bme(), tempOversampling(tempOS), humOversampling(humOS), pressOversampling(pressOS),
      gasHeaterTemp(gasTemp), gasHeaterDur(gasDur) {}

bool BME680Manager::begin()
{
    if (!this->bme.begin())
    {
        return false;
    }

    this->bme.setTemperatureOversampling(this->tempOversampling);
    this->bme.setHumidityOversampling(this->humOversampling);
    this->bme.setPressureOversampling(this->pressOversampling);
    this->bme.setGasHeater(this->gasHeaterTemp, this->gasHeaterDur);
    return true;
}

bool BME680Manager::performReading()
{
    return this->bme.performReading();
}

float BME680Manager::getTemperature() const
{
    return this->bme.temperature;
}

float BME680Manager::getHumidity() const
{
    return this->bme.humidity;
}

float BME680Manager::getPressure() const
{
    return this->bme.pressure / 100.0;
}

float BME680Manager::getGasResistance() const
{
    return static_cast<float>(this->bme.gas_resistance) / 1000.0f;
}

SensorData BME680Manager::getSensorData() const
{
    return SensorData{this->getTemperature(), this->getHumidity(), this->getPressure(), this->getGasResistance()};
}