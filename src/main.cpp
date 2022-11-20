#include "main.h"

//==========================     SETUP RTOS       ========================

QueueHandle_t dataBMESensorQueue;
QueueHandle_t dataCalibrateQueue;


TimerHandle_t wifiTimer;


void smartConfigWiFi(TimerHandle_t xTimer)
{
	log_e("--> Wifi is scanning....");
	for (size_t wifi_connectTrialCount = 0; wifi_connectTrialCount < WIFI_MAX_CONNECT_TRIAL; wifi_connectTrialCount++)
	{
		if (WiFi.smartConfigDone())
		{
			connectionStatus_st.wifiStatus = status_et::CONNECTED;
			log_e("Wifi connected!");
		}
	}

	connectionStatus_st.wifiStatus = status_et::DISCONNECTED;
	ESP_LOGE("Wifi disconnected!");
}

void smartConfigWiFi_Task(void *parameters)
{
	for (;;)
	{
		if ((xTimerIsTimerActive(wifiTimer) == pdFALSE) && Button_isPressed(PIN_BUTTON_1)) 
		{
			xTimerStart(wifiTimer, 0);
			connectionStatus_st.wifiStatus = status_et::SCANNING;
		} 
		if ((xTimerIsTimerActive(wifiTimer) == pdTRUE) && !Button_isPressed(PIN_BUTTON_1)) 
		{
			xTimerStop(wifiTimer, 0);
			connectionStatus_st.wifiStatus = status_et::DISCONNECTED;
		} 
		vTaskDelay((TickType_t) 100 / portTICK_PERIOD_MS);
	}
}


void getDataFromSensor_Task(void *parameters)
{
	struct sensorData sensorDataTemp_st;
	struct calibData calibDataTemp_st;
	for(;;)
	{
		if (connectionStatus_st.bmeSensor == status_et::CONNECTED)
		{
            bme_readData(sensorDataTemp_st.temperature, sensorDataTemp_st.humidity, sensorDataTemp_st.pressure_u32);

			if (uxQueueSpacesAvailable(dataBMESensorQueue) < (UBaseType_t)4)
			{
				xQueueSend(dataBMESensorQueue, &(sensorDataTemp_st.temperature), NO_WAIT);
				xQueueSend(dataBMESensorQueue, &(sensorDataTemp_st.humidity), NO_WAIT);
				xQueueSend(dataBMESensorQueue, &(sensorDataTemp_st.pressure_u32), NO_WAIT);
			}

		} else 
		{
			log_e("BME sensor disconnected!");
		}

		sensorData_st = sensorDataTemp_st;
		vTaskDelay(SAMPLING_PERIOD);
	}	
}


void dataManagement_Task(void *parameters)
{
	for (;;)
	{
		struct sensorData sensorDataTemp_st(dataBMESensorQueue);

		DS3231_getStringDateTime(realTime, DateTime::TIMESTAMP_FULL , dateTime_string);
		createSensorDataString(sensorDataString, NAME_DEVICE, dateTime_string ,sensorDataTemp_st);
		DS3231_getStringDateTime(realTime, DateTime::TIMESTAMP_DATE, nameFileSaveData);
		SDcard_saveStringDataToFile(&connectionStatus_st, sensorDataString);
		createMessageMQTTString(messageData, (const char *)espID, timeClient, sensorDataTemp_st);
		MQTT_postData(messageData.c_str(), &connectionStatus_st, mqttClient);

		vTaskDelay(((TickType_t) 5000 / portTICK_PERIOD_MS));
	}
	
}

void setup()
{
    Serial.begin(SERIAL_DEBUG_BAUDRATE);
    log_e("Booting...");
    version_info();
    WIFI_init();
    Button_init(PIN_BUTTON_1, INPUT, BUTTON_STATE_PULL_UP);
    Wire.begin(PIN_SDA_GPIO, PIN_SCL_GPIO, I2C_CLOCK_SPEED);
    bme_initialize(Wire);
	DS3231_init(realTime, timeClient, Wire, connectionStatus_st);
#ifdef USING_MQTT
	MQTT_initClient(topic, espID, mqttClient, &connectionStatus_st);
	timeClient.begin();
#endif
#ifdef USING_SDCARD
	SDcard_init(PIN_NUM_CLK, PIN_NUM_MISO, PIN_NUM_MOSI, PIN_CS_SD_CARD, &connectionStatus_st);
#endif
    log_e("Init Done");

    dataCalibrateQueue	= xQueueCreate(7, sizeof(uint32_t));
	dataBMESensorQueue	= xQueueCreate(3, sizeof(float));

	wifiTimer = xTimerCreate("ButtonTimer", BUTTON_PRESS_DURATION, pdFALSE, (void *) 0, smartConfigWiFi);

	xTaskCreatePinnedToCore(smartConfigWiFi_Task, "Smart config", STACK_SIZE, NULL, 1, NULL, 0);
	xTaskCreatePinnedToCore(dataManagement_Task, "Data management", STACK_SIZE, NULL, 1, NULL, 0);
	xTaskCreatePinnedToCore(getDataFromSensor_Task, "Get sensor data", STACK_SIZE, NULL, 1, NULL, 1);
	log_e("Finished to Create task!");
}

void loop()
{
    
}