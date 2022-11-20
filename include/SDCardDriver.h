/**
 * @file file.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-11-11
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#pragma once
#ifndef SDCARDDRIVER_H
#define SDCARDDRIVER_H

#include "esp_log.h"
#include <stdarg.h>
#include "globals.h"
#include "DeviceManager.h"
#include <SD.h>

#define ERROR_SD_CARD_INIT_FAILED 		(0x31)
#define ERROR_SD_CARD_READ_FILE_FAILED 	(0x32)
#define ERROR_SD_CARD_WRITE_FILE_FAILED (0x33)
#define ERROR_SD_CARD_FILE_NOT_FOUND 	(0x34)


/**
 * @brief Initialize SD Card
 * 
 * @param[in] _pinSCK:  SCK pin
 * @param[in] _pinMISO: MISO pin
 * @param[in] _pinMOSI: MOSI pin
 * @param[in] _pinCS:   ChipSelect pin
 * @param[in] _connecctionStatus: pointer to struct status connection
 * @return ERROR_CODE
 */
ERROR_CODE SDcard_init(uint8_t _pinSCK,
					   uint8_t _pinMISO,
					   uint8_t _pinMOSI,
					   uint8_t _pinCS,
					   struct connectionStatus *_connectionStatus);

/**
 * @brief	Doc file tu trong the nho
 * 
 * @param[in]  	fileName_string                 : ten file
 * @param[in]	numberOfRequestedByte_u32		: so byte muon doc
 * @param[out]  fileContent_string				: chuoi chua noi dung file
 * @param[out]  numberOfReadByte_u32			: so byte doc duoc
 * 
 * @return  ERROR_CODE
 */
ERROR_CODE SDcard_readFile( const char *fileName_string,
							char *fileContent_string,
							const uint32_t numberOfRequestedByte_u32,
							uint32_t *numberOfReadByte_u32);


/**
 * @brief 
 * 
 * @param[in]   _connectionStatus: struct connection Status
 * @param[in]   _nameFile: name file save calibdata
 * @param[in]   _format: format store data in file
 * @param[out]  __VA_ARGS__ List argument (pointer)
 * @return ERROR_CODE 
 */
ERROR_CODE SDcard_readCalibDataFromFile(struct connectionStatus *_connectStatus,
										const char *_nameFile,
										const char *_format,
										...);


/**
 * @brief Save sensor data to SDcard
 * 
 * @param[in] fileContent_string: string save to file
 * @param[in] _connecctionStatus: pointer to struct store all connection status
 * @return ERROR_CODE 
 */
ERROR_CODE SDcard_saveStringDataToFile( struct connectionStatus *_connectStatus,
										const char *fileContent_string);


#endif