/**
 * @file WiFiManager.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-11-11
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef WIFIMANAGER_H
#define WIFIMANAGER_H

#include <WiFi.h>
#include <string>
#include "globals.h"
#include "configs.h"
#include "esp_log.h"

#define ERROR_WIFI_INIT_FAILED (0xa1)

/**
 * @brief WiFi initialized
 * 
 * @return ERROR_CODE 
 */
ERROR_CODE WIFI_init();


#endif