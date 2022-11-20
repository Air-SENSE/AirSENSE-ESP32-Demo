#ifndef _MAIN_H_
#define _MAIN_H_

// Arduino core @ ${ARDUINO_ESP32}/cores/esp32
#include <Arduino.h>


// C/C++ lib
#include <stdarg.h>
#include <string>

// Arduino third-party lib @ ${ARDUINO_ESP32}/libraries
#include <SPI.h>
#include <WiFi.h>
#include "Wire.h"

#include <PubSubClient.h>
#include <NTPClient.h>
#include <WiFiUdp.h>
#include <WiFiClient.h>
#include <WiFiServer.h>
#include <ArduinoJson.h>

// ESP-IDF SDK @ ${ESP_IDF}/components && ${ARDUINO_ESP32}/tools/sdk/include
#include "esp_log.h"
#include "esp_system.h"
#include "esp_vfs_dev.h"
#include "esp_spi_flash.h"
#include "esp_task_wdt.h"
#include "esp_heap_caps.h"
#include "driver/adc.h"
#include "driver/gpio.h"
#include "driver/uart.h"
#include "driver/spi_slave.h"
#include "freertos/task.h"
#include "freertos/FreeRTOS.h"


// local headers
#include "configs.h"
#include "globals.h"

#include "DeviceManager.h"
#include "DataStructure.h"
#include "WiFiManager.h"
#include "MQTTConnection.h"
#include "DS3231Driver.h"
#include "SDCardDriver.h"
#include "BMESensor.h"
#include "ButtonDriver.h"



/******************************************************************************
 * Global variables definition
 */


esp_log_level_t log_level = LOG_LEVEL;
const int log_level_min = 0, log_level_max = 5;

const char *NAME = "AirSENSE";
const char *prompt = "AirSENSE> ";

char dateTime_string[25];
char dataCalib_string[50];
char sensorDataString[64];
String messageData;

struct sensorData sensorData_st;

struct calibData calibData_st;

struct connectionStatus connectionStatus_st;

char espID[10];
char topic[32];

WiFiUDP ntpUDP;
WiFiClient espClient;
PubSubClient mqttClient(espClient);
NTPClient timeClient(ntpUDP, "de.pool.ntp.org", 3600*7, 60000);

const char fileNameCalib[] = "calib.txt";			// file chua cac gia tri calib
char nameFileSaveData[12];							// ten file luu du lieu cua sensor theo tung ngay

const char* remote_host_string = "www.google.com";
RTC_DS3231 realTime;
BME280I2C bmeSensor;


/******************************************************************************
 * Constants
 */

const char* const log_level_list[] = {
    "SILENT", "ERROR", "WARNING", "INFO", "DEBUG", "VERBOSE",
};


/******************************************************************************
 * Functions
 */

void verbose() {
    log_level = esp_log_level_t( min((log_level + 1), log_level_max) );
    esp_log_level_set(NAME, log_level);
    ESP_LOGE(NAME, "Current log level: %s", log_level_list[log_level]);
}

void quiet() {
    log_level = esp_log_level_t( max((log_level - 1), log_level_min) );
    esp_log_level_set(NAME, log_level);
    ESP_LOGE(NAME, "Current log level: %s", log_level_list[log_level]);
}


void version_info() {
    esp_chip_info_t info;
    esp_chip_info(&info);
    ESP_LOGE(NAME, "IDF Version: %s", esp_get_idf_version());
    ESP_LOGE(NAME, "Chip info:");
    ESP_LOGE(NAME, "\tmodel: %s", info.model == CHIP_ESP32 ? "ESP32" : "???");
    ESP_LOGE(NAME, "\tcores: %d", info.cores);
    ESP_LOGE(NAME, "\tfeature: %s%s%s/%s-Flash: %d MB", 
        info.features & CHIP_FEATURE_WIFI_BGN ? "/802.11bgn" : "",
        info.features & CHIP_FEATURE_BLE ? "/BLE" : "",
        info.features & CHIP_FEATURE_BT ? "/BT" : "",
        info.features & CHIP_FEATURE_EMB_FLASH ? "Embedded" : "External",
        spi_flash_get_chip_size() / (1024 * 1024));
    ESP_LOGE(NAME, "\trevision number: %d", info.revision);
    ESP_LOGE(NAME, "Firmware Version: RTOS 20221");
    ESP_LOGE(NAME, "Project AirSENSE - Firmware");
    ESP_LOGE(NAME, "Designed by SPARC Lab");
}


#endif