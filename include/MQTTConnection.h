/**
 * @file MQTTConnection.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-11-11
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#pragma once
#ifndef MQTTCONNECTION_H
#define MQTTCONNECTION_H

#include "Arduino.h"
#include "WiFi.h"
#include "esp_log.h"
#include "globals.h"
#include "configs.h"
#include <NTPClient.h>
#include <WiFiClient.h>
#include <WiFiUdp.h>
#include <PubSubClient.h>



#define KEEP_ALIVE_PERIOD 45
#define MQTT_PORT   (1884)
#define MQTT_USER   "test"
#define MQTT_PASSWORD   "testadmin"

#define MQTT_SERVER_IP_ADDRESS "103.130.212.210"
#define MQTT_SERVER_PORT  	1885U

#define ERROR_MQTT_INIT_FAILED		(0x51)
#define ERROR_MQTT_POST_DATA_FAILED (0X52)


struct MQTTInfo
{
    String broker;
    uint16_t port;
	String mqttTopicPub;
	String mqttTopicSub;
	String mqttUser;	
	String mqttPWD;
	String mqtt_ID;
};

/**
 * @brief	ham de khoi tao ket noi mqtt
 * @param[in]	_topic  topic cua server tra ve
 * @param[in]	_espID  ID cua esp
 * @param[out]	_mqttClient  bien luu tru ket noi
 * @return ERROR_CODE
 */
ERROR_CODE MQTT_initClient( char*			 		_topic,
					 	 	char*			 		_espID,
					 	 	PubSubClient& 	 		_mqttClient,
						 	struct connectionStatus *_connectionStatus);



/**
 * @brief	ham de gui data len MQTT
 * 
 * @param[in] 	_message : chuoi du lieu
 * @param[in]	_mqttClient: bien luu tru ket noi
 * @param[in]	_timeClient: bien lay thoi gian tu server "de.pool.ntp.org"
 * @param[in] 	_nameDevice: ten thiet bi
 * @return  ERROR_CODE
 */
ERROR_CODE MQTT_postData(const char *_message,
					     struct connectionStatus 	*_connectionStatus,
					     PubSubClient&  			_mqttClient);

#endif
