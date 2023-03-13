#ifndef _DS18B20_H_
#define _DS18B20_H_
#include "STC8H.h"
#include "Delay.h"
#include "string.h"

sbit DS18B20_DQ = P2^3;

unsigned int DS18B20_CheckDevice(void);
unsigned int DS18B20_WaitReady(void);
void DS18B20_Init();
void DS18B20_Reset();
extern void DS18B20_Delay(unsigned int n);
extern void DS18B20_Write_Byte(unsigned char dat);
extern unsigned char DS18B20_Read_Byte();
//extern bit DS18B20_Init();
extern unsigned int Get_temp(void);
bit DS18B20_Read_Bit();
void DS18B20_Write_Bit(bit dat);
extern unsigned char flag_temper;

#endif