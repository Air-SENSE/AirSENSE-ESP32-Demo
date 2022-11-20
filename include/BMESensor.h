/**
 * @file BMESensor.h
 * @author SPARC member
 * @brief BME280 Sensor library
 * @version 0.1
 * @date 2022-11-19
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef BMESENSOR_H
#define BMESENSOR_H

#include <Wire.h>
#include "esp_log.h"
#include "globals.h"
#include "BME280I2C.h"
#include "configs.h"

#define CONFIG_ARDUHAL_LOG_COLORS 1

#define ERROR_BME_INIT_FAILED       0xd0
#define ERROR_BME_DET_DATA_FAILED   0xd1


/**
 * @brief Initialize BME280 Sensor
 * 
 * @param[in] _wire: Wire I2C
 * 
 * @return ERROR_CODE 
 * @retval ERROR_NONE: if success
 * @retval ERROR_BME_INIT_FAILED: if failed
 */
ERROR_CODE bme_initialize(TwoWire &_wire);


/**
 * @brief Get temperature, humidity and presure value from BME280 Sensor 
 * 
 * @param[out] _temperature: temperature value (℃)
 * @param[out] _humidity: humidity value (%)
 * @param[out] _pressure: pressure value (atm)
 * 
 * @return ERROR_CODE
 * @retval ERROR_NONE: if success
 * @retval ERROR_BME_DET_DATA_FAILED: if failed
 */
ERROR_CODE bme_readData(float &_temperature, float &_humidity, float &_pressure);

#endif