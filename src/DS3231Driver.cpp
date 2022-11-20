#include "DS3231Driver.h"

ERROR_CODE DS3231_init(RTC_DS3231& _realTime, NTPClient&  _timeClient, TwoWire &_wire, struct connectionStatus _connectionStatus)
{
	if (_realTime.begin(&_wire))			// khoi dong module RTC
	{
		log_e("RTC module initialized successfully!");        		
		connectionStatus_st.ds3231Module = status_et::CONNECTED;
		if (_connectionStatus.wifiStatus == status_et::CONNECTED)		// kiem tra co ket noi wifi
		{
			if (Ping.ping(remote_host_string))				// kiem tra ping duong dan "www.google.com"
			{
				_timeClient.update();						// cap nhat thoi gian cho RTC	
				uint32_t epochTime_u32 = _timeClient.getEpochTime();
				_realTime.adjust(DateTime(epochTime_u32));			// Set the date and flip the Oscillator Stop Flag
				log_e("Updatetime DS3231....");
				log_e("Updatetime success. Current time: %u.", _realTime.now().unixtime());
			}
			return ERROR_NONE;
		} else 
		{
			log_e("Wifi is disconnect.");
			log_e("Updatetime failed.");
			return ERROR_RTC_UPDATE_TIME_FAILED;
		}

	} else {
		log_e("RTC module initialized failed!");		
		connectionStatus_st.ds3231Module = status_et::DISCONNECTED;
		return ERROR_RTC_INIT_FAILED;
	}
}

ERROR_CODE DS3231_getStringDateTime(RTC_DS3231 _realTime, DateTime::timestampOpt _opt, char *_dateTime_string)
{
	if (connectionStatus_st.ds3231Module ==  status_et::CONNECTED)		// kiem tra thoi gian co hop le
	{
		strcpy(_dateTime_string, (_realTime.now().timestamp(_opt).c_str()));		// in thoi gian hien tai ra Serial

		log_e("Get DateTime successfully!");
		return ERROR_NONE;
	} else {
		log_e("Get DateTime failed.");
		return ERROR_RTC_GET_STRING_DATETIME_FAILED;
	}
}


