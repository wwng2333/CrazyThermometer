#ifndef __IIC_H__
#define __IIC_H__

#include "STC8H.h"

unsigned int LM75_Update(void);
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