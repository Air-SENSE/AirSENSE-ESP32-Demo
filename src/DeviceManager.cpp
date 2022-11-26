#include "DeviceManager.h"

ERROR_CODE initAllSensor()
{
    if (  
            (bme_initialize(Wire)  == ERROR_NONE)                                   &&
            (Button_init(PIN_BUTTON_1, INPUT, 1) == ERROR_NONE)
        )
    {
        return ERROR_NONE;
    } else {
        return ERROR_SENSOR_INIT_FAILED;
    }
}

ERROR_CODE isSensorDisconnected(status_et _statusDevice)
{
    if (_statusDevice == status_et::DISCONNECTED)
    {
        return ERROR_SENSOR_DISCONNECTED;
    } else {
        return DEVICE_CONNECTED;
    }
}

ERROR_CODE isAllSensorDisconnected(struct connectionStatus _connectionStatus)
{
    if (
        isSensorDisconnected(_connectionStatus.bmeSensor)       == ERROR_SENSOR_DISCONNECTED 
        )
    {
        log_e("All sensors disconnected");
        return ERROR_SENSOR_ALL_DISCONNECTED;
    } else {
        return ERROR_NONE;
    }
}
