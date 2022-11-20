/*
 * @file DataStructure.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-11-11
 * 
 * @copyright Copyright (c) 2022
 * 
*/

#ifndef DATASTRUCTURE_H
#define DATASTRUCTURE_H

#include <Arduino.h>
#include <string>
#include "esp_log.h"
#include "configs.h"
#include <ArduinoJson.h>
#include <NTPClient.h>

#define ERROR_DATA_CREATE_STRINGDATA_FAILED 0x91




struct calibData {
    uint32_t temperature_calibInt_u32;
    uint32_t humidity_calibInt_u32;
    uint32_t pm1_calibInt_u32;
    uint32_t pm10_calibInt_u32;
    uint32_t pm25_calibInt_u32;
    uint32_t temperature_calibFloat_u32;
    uint32_t humidity_calibFloat_u32;

    calibData() {     // initialation function for struct (C++ style)
        this->temperature_calibInt_u32      = 0;
        this->humidity_calibInt_u32         = 0;
        this->pm1_calibInt_u32              = 0;
        this->pm10_calibInt_u32             = 0;
        this->pm25_calibInt_u32             = 0;
        this->temperature_calibFloat_u32    = 0;
        this->humidity_calibFloat_u32       = 0;
    }
};



/**
 * @brief Create a string from sensor data for storing in the SD card
 * 
 * @param[out] _calibDataString: pointer char*, use to store string
 * @param[in]  _calibData: struct calibdata
 * @return ERROR_CODE 
 */
ERROR_CODE creatCalibDataString(char *_calibDataString, struct calibData _calibData);

struct sensorData {
    float      temperature;
    float      humidity;    
    float      pressure_u32;
    uint32_t   pm1_u32;
    uint32_t   pm25_u32;
    uint32_t   pm10_u32;
    uint32_t   pm25_min_u32;
    uint32_t   pm25_max_u32;
    float      o3_ppb;
    float      o3_ppm;
    float      o3_ug;
    float      o3_ppb_min;
    float      o3_ppm_min;
    float      o3_ug_min;
    float      o3_ppb_max;
    float      o3_ppm_max;
    float      o3_ug_max;

    sensorData() 
    {
        this->temperature	  = 0;
        this->humidity		  = 0;
        this->pressure_u32    = 0;
        this->pm1_u32         = 0;
        this->pm25_u32        = 0;
        this->pm10_u32        = 0;
        this->pm25_min_u32    = 0;
        this->pm25_max_u32    = 0;
        this->o3_ppb          = 0;
        this->o3_ppm          = 0;
        this->o3_ug           = 0;
        this->o3_ppb_min      = 100;
        this->o3_ppm_min      = 100;
        this->o3_ug_min       = 100;
        this->o3_ppb_max      = 0;
        this->o3_ppm_max      = 0;
        this->o3_ug_max       = 0;
    };

    sensorData(QueueHandle_t queue1)
    {
            xQueueReceive(queue1, (void *)&(this->temperature)  , NO_WAIT);
            xQueueReceive(queue1, (void *)&(this->humidity)     , NO_WAIT);
            xQueueReceive(queue1, (void *)&(this->pressure_u32) , NO_WAIT);
        
    }

    sensorData operator=(const sensorData _sensorData_temp)
    {
        this->temperature	 = _sensorData_temp.temperature;
        this->humidity		 = _sensorData_temp.humidity;
        this->pressure_u32	 = _sensorData_temp.pressure_u32;
        this->pm1_u32        = _sensorData_temp.pm1_u32;
        this->pm25_u32       = _sensorData_temp.pm25_u32;
        this->pm10_u32       = _sensorData_temp.pm10_u32;
        this->pm25_min_u32   = _sensorData_temp.pm25_min_u32;
        this->pm25_max_u32   = _sensorData_temp.pm25_max_u32;
        this->pressure_u32	 = _sensorData_temp.pressure_u32;
        this->o3_ppb         = _sensorData_temp.o3_ppb;
        this->o3_ppm         = _sensorData_temp.o3_ppm;
        this->o3_ug          = _sensorData_temp.o3_ug;
        this->o3_ppb_min     = _sensorData_temp.o3_ppb_min;
        this->o3_ppm_min     = _sensorData_temp.o3_ppm_min;
        this->o3_ug_min      = _sensorData_temp.o3_ug_min;
        this->o3_ppb_max     = _sensorData_temp.o3_ppb_max;
        this->o3_ppm_max     = _sensorData_temp.o3_ppm_max;
        this->o3_ug_max      = _sensorData_temp.o3_ug_max;

        return _sensorData_temp;
    }
};


/**
 * @brief Create a string
 * 
 * @param[out] _calibDataString: pointer char*, use to store string
 * @param[in]  _calibData: struct calibdata
 * @return ERROR_CODE 
 */
ERROR_CODE createSensorDataString(char *_sensorDataString,
                                  const char *_nameDevice,
                                  const char *_dateTimeString,
                                  struct sensorData _sensorData_st);

/**
 * @brief Create a MQTT string
 * 
 * @param[out] _calibDataString: pointer char*, use to store string
 * @param[in]  _calibData: struct calibdata
 * @return ERROR_CODE 
 */
ERROR_CODE createMessageMQTTString( String &messageMQTTString,
                                    const char *_espID,
                                    NTPClient& _timeClient,
                                    struct sensorData _sensorData_st);


#endif