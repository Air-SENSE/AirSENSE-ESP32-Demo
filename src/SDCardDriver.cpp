#include "SDCardDriver.h"


ERROR_CODE SDcard_init(uint8_t _pinSCK,
					   uint8_t _pinMISO,
					   uint8_t _pinMOSI,
					   uint8_t _pinCS,
					   struct connectionStatus *_connectionStatus)
{
	SPI.begin(_pinSCK, _pinMISO, _pinMOSI, _pinCS);
	pinMode(SS, OUTPUT);

	if (SD.begin(_pinCS))
	{
		_connectionStatus->sdCardStatus = status_et::CONNECTED;
		log_e("SD init success.");
		return ERROR_NONE;
	}
	else
	{
		_connectionStatus->sdCardStatus = status_et::DISCONNECTED;
		log_e("SD init false.");
		return ERROR_SD_CARD_INIT_FAILED;		
	}
}


ERROR_CODE SDcard_readFile( const char *fileName_string,
							char *fileContent_string,
							const uint32_t numberOfRequestedByte_u32,
							uint32_t *numberOfReadByte_u32)
{
	File readFile;
	readFile = SD.open(fileNameCalib, FILE_READ);
	if (readFile)			// kiem tra tinh trang mo file co thanh cong
	{
		String buffer_string = "";
		numberOfReadByte_u32 = 0;
		while (readFile.available() && ((*numberOfReadByte_u32) < numberOfRequestedByte_u32) )
		{
			fileContent_string[(*numberOfReadByte_u32)] = (char)readFile.read();
			(*numberOfReadByte_u32)++;
		}
		readFile.close();
		return ERROR_NONE;
	}	
	else{
		return ERROR_SD_CARD_READ_FILE_FAILED;	 
	}
}


ERROR_CODE SDcard_readCalibDataFromFile(struct connectionStatus *_connectStatus,
										const char *_nameFile,
										const char *_format,
										...)
{
	if (_connectStatus->sdCardStatus == status_et::CONNECTED)
	{
		File readFile;
		readFile = SD.open(_nameFile, FILE_READ);
		if (readFile)			// kiem tra tinh trang mo file co thanh cong
		{
			_connectStatus->sdCardStatus = status_et::READING_DATA;
			char fileContent_string[35];

			for (size_t i = 0; (i < 34) && (readFile.available()); i++)
			{
				fileContent_string[i] = (char)readFile.read();
			}

			va_list argumentsList;
			va_start(argumentsList, _format);
			vsscanf(fileContent_string, _format, argumentsList);
			va_end(argumentsList);

			readFile.close();
			_connectStatus->sdCardStatus = status_et::CONNECTED;
			log_e("SD card read calibrate data successfully!");
			return ERROR_NONE;
		} else {
			log_e("File not found!");
			log_e("SD card read calibrate data failed!");
			return ERROR_SD_CARD_FILE_NOT_FOUND;
		}
	} else {
		log_e("SD card disconnected!");
		log_e("SD card read calibrate data failed!");
		return ERROR_SD_CARD_READ_FILE_FAILED;
	}
}


ERROR_CODE SDcard_saveStringDataToFile( struct connectionStatus *_connectStatus,
										const char *fileContent_string)
{
	if (_connectStatus->sdCardStatus == status_et::CONNECTED)
	{
		File writeFile;
		char locationFileSaveData[30] = "/";
		strcat(locationFileSaveData, nameFileSaveData);
		strcat(locationFileSaveData, ".txt");
		writeFile = SD.open(locationFileSaveData, FILE_APPEND);		// mo file de ghi du lieu
		if (writeFile)											// kiem tra trang thai mo file co thanh cong
		{
			_connectStatus->sdCardStatus = status_et::WRITING_DATA;
			writeFile.println(fileContent_string);		// ghi chuoi ki tu chua du lieu vao file
			writeFile.close();							// dong file
			_connectStatus->sdCardStatus = status_et::CONNECTED;
			log_e("%s", fileContent_string);
			log_e("SD card write sensor data to file successfully!");
			return ERROR_NONE;
		}
		else
		{
			log_e("Can't open file to write!");
			log_e("SD card write sensor data to file failed!");
			return ERROR_SD_CARD_FILE_NOT_FOUND;
		}
	} else {
		log_e("SD card disconnected!");
		log_e("SD card write data failed!");
		return ERROR_SD_CARD_READ_FILE_FAILED;
	}
}