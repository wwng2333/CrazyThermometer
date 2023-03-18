#ifndef __IAP_H__
#define __IAP_H__

#include "STC8H.h"

void IapIdle();
char IapRead(int addr);
void IapProgram(int addr, char dat);
void IapErase(int addr);

#endif