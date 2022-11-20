/*
 * File: configs.h
 * Authors: Hank <lctuyenvn@gmail.com>
 * Create: 2019-04-17 16:51:03
 *
 * Copyright (c) 2019 EmBCI. All right reserved.
 *
 * Modify this file to quickly configure ESP32_Sandbox,
 * which is the firmware of ESP32 used in project EmBCI.
 */

#ifndef CONFIGS_H
#define CONFIGS_H

//========================== DEFINE FOR WIFI ========================

#define USING_WIFI_CONFIG
const char ssid[] = "BK Star";
const char pass[]  = "bkstar2021";

//========================== DEFINE FOR LOGGING ========================



// Log level, choose one from:
//  5 ESP_LOG_VERBOSE
//  4 ESP_LOG_DEBUG
//  3 ESP_LOG_INFO
//  2 ESP_LOG_WARN
//  1 ESP_LOG_ERROR
//  0 ESP_LOG_NONE
#define LOG_LEVEL        ESP_LOG_DEBUG


#ifdef LOG_LOCAL_LEVEL
    #undef LOG_LOCAL_LEVEL
    #define LOG_LOCAL_LEVEL ESP_LOG_VERBOSE
    // #define LOGLOCAL_LEVEL ESP_LOG_NONE
#endif

#define USING_SDCARD
#define USING_MQTT
#define USING_RTC

#define SERIAL_DEBUG_BAUDRATE   (9600)

#define ERROR_CODE int
#define ERROR_NONE (0x00)


//========================== DEFINE SPI  ========================

#define PIN_NUM_MISO    (21)
#define PIN_NUM_MOSI    (19)
#define PIN_NUM_CLK     (18)
#define PIN_CS_SD_CARD  (5)


//========================== DEFINE I2C ========================

#define PIN_SDA_GPIO    26
#define PIN_SCL_GPIO    27
#define I2C_CLOCK_SPEED 100000U
#define RTC_I2C_ADDRESS (0x68)

//========================== DEFINE LED RGB ========================

#define PIN_NEO_PIXEL   (23)

//========================== DEFINE 2 BUTTON ========================

#define PIN_BUTTON_1    (35)
#define PIN_BUTTON_2    (34)

//========================== DEFINE THIET BI ========================

#define NAME_DEVICE "AirSENSE_RTOS"
#define NUM_TIMERS   (1)

// dinh nghia kieru gia tri cho cam bien
#define FIXPOINT_32_16 uint32_t    // kieru du lieu fix point dung cho cam bien

//=========================== Define cac chu ki =============================

#define MQTT_SENDDATA_PERIOD	    (uint32_t)10000
#define SD_WRITEDATA_PERIOD		    (uint32_t)10000
#define WIFI_RECONNECT_PERIOD	    (uint32_t)6000
#define BUTTON_PRESSED_DURATION 	(uint32_t)4000
#define WIFI_MAX_CONNECT_TRIAL      (uint8_t)100

#define NO_WAIT     ((TickType_t) 0 / portTICK_PERIOD_MS)
#define SAMPLING_PERIOD  ((TickType_t) 5000 / portTICK_PERIOD_MS)
#define BUTTON_PRESS_DURATION	((TickType_t) 3000 / portTICK_PERIOD_MS)
#define STACK_SIZE       ((1024U) * 30)     // byte

enum status_et
{
    DISCONNECTED,
    CONNECTED,
    CONNECTION_LOST,
    SCANNING,
    SENDING_DATA,
    READING_DATA,
    WRITING_DATA
};

struct connectionStatus
{
    status_et wifiStatus;
    status_et sdCardStatus;
    status_et mqttConnection;
    status_et ds3231Module;
    status_et bmeSensor;
};



#endif // CONFIGS_H