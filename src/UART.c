#include "UART.h"
#include "string.h"
#include "IAP.h"

bit busy;
char wptr;
char rptr;
char buffer[16];

volatile bit OnMessage = 0;
volatile unsigned int SendTemp = 0;

void UartIsr() interrupt 4
{
    extern bit OnMessage;
    if (TI)
    {
        TI = 0;
        busy = 0;
    }
    if (RI)
    {
        RI = 0;
        buffer[wptr++] = SBUF;
        wptr &= 0x0f;
        if(SBUF == 0x0A) OnMessage = 1;
    }
}

void UartInit()
{
    P_SW2 |= 0x80;
    SCON = 0x50;
    TMOD = 0x00;
    TL1 = BRT;
    TH1 = BRT >> 8;
    TR1 = 1;
    AUXR = 0x40;
    wptr = 0x00;
    rptr = 0x00;
    busy = 0;
    ES = 1;
    EA = 1;
    UartSendOK();
    P_SW2 &= ~0x80;
}

void UartSend(char dat)
{
    while (busy);
    busy = 1;
    SBUF = dat;
}

/*
char putchar(char ch)
{
    SBUF = ch;
    while(TI == 0);
    TI = 0;
    return ch;
}
*/

void UartSendStr(char *p)
{
    while (*p)
        UartSend(*p++);
}

void UartInitReport(char *p)
{
    //UartSendStr(p);
    //UartSendStr(":inited.\r\n");
}

void UartSendOK(void)
{
    UartSendStr("\r\nOK\r\n");
}

void UartOnMessage(void)
{    
    //UartSendStr(buffer);
    if(strcmp(buffer, "AT\r\n") == 0)
    {
        UartSendOK();
    } else if(strcmp(buffer, "AT+RST\r\n") == 0) {
        P_SW2 |= 0x80;
        IAP_CONTR |= 0x20;
    } else if(strcmp(buffer, "AT+TEMP\r\n") == 0) {
        SendTemp = 1;
    } else if(strcmp(buffer, "AT+IAPR\r\n") == 0) {
        IAP_ReadBright();
    } else if(strcmp(buffer, "AT+IAPW\r\n") == 0) {
        IAP_SaveBright();
    } else {
        UartSendStr("ERROR\r\n");
    }
    memset(buffer, 0, sizeof(buffer)/ sizeof(char));
    wptr = 0;
    OnMessage = 0;
}