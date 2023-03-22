#ifndef __UART_H__
#define __UART_H__

#include "STC8H.h"
#define FOSC 11059200UL
#define BRT (65536 - FOSC / 115200 / 4)

void UartIsr();
void UartInit();
void UartSend(char dat);
void UartSendStr(char *p);
void UartInitReport(char *p);
void UartOnMessage(void);
void UartSendOK(void);
void ClearBuffer(char *buff);
#endif