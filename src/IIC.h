#ifndef __IIC_H__
#define __IIC_H__

#include "STC8H.h"

void I2C_Isr();
void LM75_Update();
unsigned int LM75_GetTemp(void);
void IIC_Init();
void IIC_Wait();
void IIC_Start();
void IIC_SendData(char dat);
void IIC_RecvACK();
char IIC_RecvData();
void IIC_SendACK();
void IIC_SendNAK();
void IIC_Stop();

#endif