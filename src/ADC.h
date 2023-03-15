#ifndef __ADC_H__
#define __ADC_H__

#include "STC8H.h"

int ADC_Read(void);
void ADC_Isr();
void ADC_Update(void);
void ADC_Init(void);

#endif