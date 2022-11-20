/**
 * @file DeviceManager.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-11-11
 * 
 * @copyright Copyright (c) 2022
 * 
 */


#ifndef DEVICEMANAGER_H
#define DEVICEMANAGER_H

// local headers
#include "configs.h"
#include "esp_log.h"
#include "MQTTConnection.h"
#include "SDCardDriver.h"
#include "ButtonDriver.h"
#include "BMESensor.h"


#define DEVICE_CONNECTED                ERROR_NONE
#define ERROR_SENSOR_DISCONNECTED       (0xc1)
#define ERROR_SENSOR_ALL_DISCONNECTED   (0xc2)
#define ERROR_SENSOR_INIT_FAILED        (0xc3)

/**
 * @brief initAllSensor
 * 
 * @param  
 * @return ERROR_CODE 
 */
ERROR_CODE initAllSensor();

/**
 * @brief 
 * 
 * @param _statusDevice 
 * @return ERROR_CODE 
 */
ERROR_CODE isSensorDisconnected(status_et _statusDevice);

/**
 * @brief 
 * 
 * @param _connectionStatus 
 * @return ERROR_CODE 
 */
ERROR_CODE isAllSensorDisconnected(struct connectionStatus _connectionStatus);


#endif /* DEVICEMANAGER_H */
