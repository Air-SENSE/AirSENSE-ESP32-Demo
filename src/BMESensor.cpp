#include "BMESensor.h"

ERROR_CODE bme_initialize(TwoWire &_wire)
{
    if (bmeSensor.begin())
    {
        log_e("BME280 Sensor initialize successfully!");
        connectionStatus_st.bmeSensor = status_et::CONNECTED;
        return ERROR_NONE;
    } else {
        log_e("BME280 Sensor initialize failed!");
        connectionStatus_st.bmeSensor = status_et::DISCONNECTED;
        return ERROR_BME_INIT_FAILED;
    }

};


ERROR_CODE bme_readData(float &_temperature, float &_humidity, float &_pressure)
{
    bmeSensor.read(_pressure, _temperature, _humidity, BME280::TempUnit::TempUnit_Celsius, BME280::PresUnit::PresUnit_atm);
    _pressure = (_pressure == NAN) ? -1 : _pressure;
    _temperature = (_temperature == NAN) ? -273 : _temperature;
    _humidity = (_humidity == NAN) ? -1 : _humidity;
    if (_pressure == -1 || _temperature == -273 || _humidity == -1)
    {
        log_e("BME280 Sensor get data failed!");
        return ERROR_BME_DET_DATA_FAILED;
    } else {
        log_e("BME280 Sensor get data successsfully!");
        return ERROR_NONE;
    }
};

