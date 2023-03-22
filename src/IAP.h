#ifndef __IAP_H__
#define __IAP_H__

#include "STC8H.h"

#define BRIGHTNESS 0x0001

void IAP_SaveBright(void);
void IAP_SetBright(void);
int IAP_GetBright(void);
void IAP_ReadBright(void);

void IapIdle();
char IapRead(int addr);
void IapProgram(int addr, char dat);
void IapErase(int addr);

#endif