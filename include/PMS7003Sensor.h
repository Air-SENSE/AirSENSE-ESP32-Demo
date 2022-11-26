/**
 * @file PMS7003Sensor.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-11-20
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef PMS7003SENSOR_H
#define PMS7003SENSOR_H

#include "HardwareSerial.h"
#include "esp_log.h"
#include "Plantower_PMS7003.h"
#include "configs.h"

Plantower_PMS7003 pmsSensor = Plantower_PMS7003();

#define ERROR_PMS_INIT_FAILED       0xe0
#define ERROR_PMS_GET_DATA_FAILED   0xe1

/**
 * @brief Initialize PMS7003 Sensor
 * 
 * @param[in] _stream: HardwareSerial stream use to communicate with MCU
 * 
 * @return ERROR_CODE 
 * @retval ERROR_NONE: if success
 * @retval ERROR_PMS_INIT_FAILED: if failed
 */
ERROR_CODE pms_init(HardwareSerial *_stream);

/**
 * @brief Get new data from PMS7003 sensor
 * 
 * @param[out] _pm_1_0: PM 1.0
 * @param[out] _pm_2_5: PM 2.5
 * @param[out] _pm_10_0: PM 10.0
 * 
 * @return ERROR_CODE 
 * @retval ERROR_NONE: if success
 * @retval ERROR_PMS_GET_DATA_FAILED: if failed
 */
ERROR_CODE pms_getdata(int32_t *_pm_1_0, int32_t *_pm_2_5, int32_t *_pm_10_0);


ERROR_CODE pms_init(HardwareSerial *_stream)
{
    if (_stream->available())
    {
        pmsSensor.init(_stream);
        log_e("PMS7003 Sensor initialize successfully!");
        return ERROR_NONE;
    } else {
        log_e("Hardware serial not available.\r\nPMS7003 Sensor initialize failed!");
        return ERROR_PMS_INIT_FAILED;
    }
}

ERROR_CODE pms_getdata(int32_t *_pm_1_0, int32_t *_pm_2_5, int32_t *_pm_10_0)
{
    pmsSensor.updateFrame();
    if (pmsSensor.hasNewData())
    {
        log_e("\nSensor Version: %d.\n", pmsSensor.getHWVersion());
        *_pm_1_0 = pmsSensor.getPM_1_0_atmos();
        *_pm_2_5 = pmsSensor.getPM_2_5_atmos();
        *_pm_10_0 = pmsSensor.getPM_10_0_atmos();

        log_e("PMS7003 Sensor get new data successfully!");
        return ERROR_NONE;
    } else {
        *_pm_1_0 = -1;
        *_pm_2_5 = -1;
        *_pm_10_0 = -1;
        log_e("PMS7003 Sensor get new data failed!");
        return ERROR_PMS_GET_DATA_FAILED;
    }
}

#endif