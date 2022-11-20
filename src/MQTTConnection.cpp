#include "MQTTConnection.h"

#ifdef USING_MQTT

MQTTInfo info;

ERROR_CODE MQTT_initClient( char*			 		_topic,
					 	 	char*			 		_espID,
					 	 	PubSubClient& 	 		_mqttClient,
						 	struct connectionStatus *_connectionStatus)
{
	uint8_t espMacAddress[6];				// mang luu dia chi MAC
	WiFi.macAddress(espMacAddress);			// lay dia chi MAC cua WIFI

	sprintf(_topic, "/V3/%x%x%x%x/", espMacAddress[0],  espMacAddress[1],  espMacAddress[2],  espMacAddress[3]);
	sprintf(_espID, "%x%x%x%x", espMacAddress[0],  espMacAddress[1],  espMacAddress[2],  espMacAddress[3]);
	
	log_e("%s",_espID);
	_mqttClient.setKeepAlive(KEEP_ALIVE_PERIOD);
	_mqttClient.setServer(MQTT_SERVER_IP_ADDRESS, MQTT_SERVER_PORT);		// cai dat server voi dia chi ip va port

 	info.broker = MQTT_SERVER_IP_ADDRESS;
    info.port = MQTT_SERVER_PORT;
    info.mqttTopicPub = String("/V3/") + _espID;
    info.mqttTopicSub = String("/cmd/") + _espID;

    

	if(_mqttClient.connect(_espID,MQTT_USER,MQTT_PASSWORD))
	{
		log_e("Topic: %s.", _topic);
		log_e("ID: %s.", _espID);
		_mqttClient.subscribe(_topic);
		_connectionStatus->mqttConnection = status_et::CONNECTED;
		log_e("MQTT initialized successfully!");
		return ERROR_NONE;
	} else {
		log_e("MQTT initialized failed!");
		_connectionStatus->mqttConnection = status_et::DISCONNECTED;
		log_e("MQTT initialized failed!");
		return ERROR_MQTT_INIT_FAILED;
	}
}


ERROR_CODE MQTT_postData(const char *_message,
					     struct connectionStatus 	*_connectionStatus,
					     PubSubClient&  			_mqttClient)
{
	
    log_e("%s",_message);
	if (_connectionStatus->wifiStatus == status_et::CONNECTED)
	{
		if (_mqttClient.connected())
		{
			_connectionStatus->mqttConnection = status_et::SENDING_DATA;

			if (_mqttClient.publish(topic, _message, true))	// kiem tra co gui dulieu len MQTT thanh cong
			{
				log_e("%s.", _message);
				_connectionStatus->mqttConnection = status_et::CONNECTED;
				_mqttClient.loop();
				log_e("MQTT send data successfully!");
				return ERROR_NONE;
			} else {
				_connectionStatus->mqttConnection = status_et::DISCONNECTED;
				log_e("MQTT post data failed!");
				return ERROR_MQTT_POST_DATA_FAILED;
			}

		} else {
			_connectionStatus->mqttConnection = status_et::DISCONNECTED;
			log_e("MQTT post data failed!");
			return ERROR_MQTT_POST_DATA_FAILED;
		}
	} else {
		log_e("WIFI  disconnected. MQTT post data failed!");
		return ERROR_MQTT_POST_DATA_FAILED;
	}
}

#endif