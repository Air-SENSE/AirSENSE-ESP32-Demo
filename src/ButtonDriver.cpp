#include "ButtonDriver.h"

ERROR_CODE Button_init(uint8_t buttonPin, uint8_t mode, int defaultStatus)
{
	pinMode(buttonPin, mode);
	if (defaultStatus < 0)
	{
		return ERROR_BUTTON_SET_STATUS_FAILED;
	} else {
		defaultStatus = (defaultStatus > 1) ? 1 : defaultStatus;
		digitalWrite(buttonPin, defaultStatus);
		return ERROR_NONE;
	}
}

bool Button_isPressed(uint8_t buttonPin)
{
	return (digitalRead(buttonPin) != BUTTON_NOT_PRESSED) ? true : false;
}
