#ifndef __MAIN_H__
#define __MAIN_H__

#include "UART.h"
#include "DigitLED.h"
#include "DS18B20.h"
#include "TouchKey.h"
#include "Timer.h"
//#include "ADC.h"
#include "IIC.h"
#include "IAP.h"
#include "PWM.h"

extern int Timer2Counter;
extern int SensorEnableCount = 0;
extern int DigitLEDDuty = 0;
extern bit UartOnMsg, SendTemp;

#endif