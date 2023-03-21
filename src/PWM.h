#ifndef __IAP_H__
#define __IAP_H__

#include "STC8H.h"

sbit CPWM = P1^0;

void PWM_Init(void);

#endif