#include "DataStructure.h"

ERROR_CODE creatCalibDataString(char *_calibDataString, struct calibData _calibData)
{
	sprintf(_calibDataString, "%u|%u|%u|%u|%u|%u|%u\n",
							  _calibData.temperature_calibInt_u32,
							  _calibData.humidity_calibInt_u32,
							  _calibData.pm1_calibInt_u32,
							  _calibData.pm10_calibInt_u32,
							  _calibData.pm25_calibInt_u32,
							  _calibData.temperature_calibFloat_u32,
							  _calibData.humidity_calibFloat_u32 );
	if (_calibDataString[0] == '\0')
	{
		log_e("Create string failed!");
		return ERROR_DATA_CREATE_STRINGDATA_FAILED;
	} else {    
        log_e("%s",_calibDataString);

		log_e("Create string complete!");
		return ERROR_NONE;
	}
}


ERROR_CODE createSensorDataString(char *_sensorDataString,
                                  const char *_nameDevice,
                                  const char *_dateTimeString,
                                  struct sensorData _sensorData_st)
{
    sprintf(_sensorDataString, "%s,%s,%.1f,%.1f,%f,%u,%u,%u,%u,%u,%.3f,%.3f,%.1f,",
                                _nameDevice,
                                _dateTimeString,
                                _sensorData_st.temperature,
                                _sensorData_st.humidity,
                                _sensorData_st.pressure_u32,
                                _sensorData_st.pm1_u32,
                                _sensorData_st.pm25_u32,
                                _sensorData_st.pm10_u32,
                                _sensorData_st.pm25_min_u32,
                                _sensorData_st.pm25_max_u32,
                                _sensorData_st.o3_ppb,
                                _sensorData_st.o3_ppm,
                                _sensorData_st.o3_ug  );
    
	if (_sensorDataString[0] == '\0')
	{
		log_e("Create string failed!");
		return ERROR_DATA_CREATE_STRINGDATA_FAILED;
	} else {
		log_e("Create string complete!");
		return ERROR_NONE;
	}
}

ERROR_CODE createMessageMQTTString( String &messageMQTTString,
                                    const char *_espID,
                                    NTPClient& _timeClient,
                                    struct sensorData _sensorData_st)
{
	_timeClient.update();

    StaticJsonDocument<200> doc;

    doc["station_id"] = _espID;
    doc["Time"] = _timeClient.getEpochTime();
    
    doc["Temperature"] = _sensorData_st.temperature;
    doc["Humidity"] = _sensorData_st.humidity;
    doc["Pressure"] = _sensorData_st.pressure_u32;
    doc["PM1"]  = _sensorData_st.pm1_u32;
    doc["PM2p5"] = _sensorData_st.pm25_u32;
    doc["PM10"] = _sensorData_st.pm10_u32;
    doc["PM2p5MAX"] = _sensorData_st.pm25_max_u32;
    doc["PM2p5MIN"] = _sensorData_st.pm25_min_u32;
    doc["O3_PPB"] = _sensorData_st.o3_ppb;
    doc["O3_PPM"] = _sensorData_st.o3_ppm;
    doc["O3_UG"]  = _sensorData_st.o3_ug;

    String output;
    serializeJson(doc, output);
    messageMQTTString = output;
    return ERROR_NONE;
}