// #include "PMS7003Sensor.h"

// ERROR_CODE pms_init(HardwareSerial *_stream)
// {
//     if (_stream->available())
//     {
//         pmsSensor.init(_stream);
//         log_e("PMS7003 Sensor initialize successfully!");
//         return ERROR_NONE;
//     } else {
//         log_e("Hardware serial not available.\r\nPMS7003 Sensor initialize failed!");
//         return ERROR_PMS_INIT_FAILED;
//     }
// }

// ERROR_CODE pms_getdata(int32_t *_pm_1_0, int32_t *_pm_2_5, int32_t *_pm_10_0)
// {
//     pmsSensor.updateFrame();
//     if (pmsSensor.hasNewData())
//     {
//         log_e("\nSensor Version: %d.\n", pmsSensor.getHWVersion());
//         *_pm_1_0 = pmsSensor.getPM_1_0_atmos();
//         *_pm_2_5 = pmsSensor.getPM_2_5_atmos();
//         *_pm_10_0 = pmsSensor.getPM_10_0_atmos();

//         log_e("PMS7003 Sensor get new data successfully!");
//         return ERROR_NONE;
//     } else {
//         *_pm_1_0 = -1;
//         *_pm_2_5 = -1;
//         *_pm_10_0 = -1;
//         log_e("PMS7003 Sensor get new data failed!");
//         return ERROR_PMS_GET_DATA_FAILED;
//     }
// }
