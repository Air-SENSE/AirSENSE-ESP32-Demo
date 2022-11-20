/**
 * @file ButtonDriver.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-11-11
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef BUTTONDRIVER_H
#define BUTTONDRIVER_H

#include "Arduino.h"
#include "configs.h"

#define BUTTON_NOT_PRESSED (1)
#define BUTTON_STATE_PULL_UP (1)


#define ERROR_BUTTON_SET_STATUS_FAILED (0xb1)

/**
 * @brief	Button init
 *
 * @param[in]	Button_init
 * @param[in]	mode: 
 * @param[in]	defaultStatus: 
 * @return  ERROR_CODE
 */
ERROR_CODE Button_init(uint8_t buttonPin, uint8_t mode, int defaultStatus);

/**
 * @brief	Button_isPressed
 *
 * @param[in]	buttonPin:  
 * @return  ERROR_CODE
 */
bool Button_isPressed(uint8_t buttonPin);

#endif