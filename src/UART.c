#include "UART.h"
#include "string.h"
#include "stdio.h"
#include "IAP.h"

bit busy;
char wptr;
char rptr;
char buffer[16];

volatile bit UartOnMsg = 0;
volatile unsigned int SendTemp = 0;
extern int SensorEnableCount;

void UartIsr() interrupt 4
{
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
        if(wptr > 16) wptr = 0; //防止溢出
        if(SBUF == 0x0A) UartOnMsg = 1;
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

char putchar(char ch)
{
    SBUF = ch;
    while(TI == 0);
    TI = 0;
    return ch;
}

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
    UartSendStr("OK\r\n");
}

void ClearBuffer(char *buff)
{
    memset(buff, 0, sizeof(buff)/ sizeof(char));
}

void UartOnMessage(void)
{    
    char cmd[8];
    int i;
    if(buffer[0] == 'A' && buffer[1] == 'T' && buffer[wptr-1] == '\n')
    {
        //UartSendStr("recv pack\r\n");
        if(buffer[2] == '+')
        {
            for(i=3; i<wptr; i++) 
            {
                if(buffer[i] == '=')
                {
                    break;
                }
            }
            memcpy(cmd, buffer+3, i);
            UartSendStr(cmd);
            UartSendStr("\n");
            //ClearBuffer(cmd);
        } else {
            UartSendOK();
        }

         if(strcmp(buffer, "AT+RST\r\n") == 0) {
            P_SW2 |= 0x80;
            IAP_CONTR |= 0x20;
        } else if(strcmp(buffer, "AT+TEMP\r\n") == 0) {
            SendTemp = SensorEnableCount;
        } else if(strcmp(buffer, "AT+IAPR\r\n") == 0) {
            IAP_ReadBright();
        } else if(strcmp(buffer, "AT+IAPW\r\n") == 0) {
            IAP_SaveBright();
        } else {
            UartSendStr("ERROR\r\n");
        }
    }
    //UartSendStr(buffer);


    //memset(buffer, 0, sizeof(buffer)/ sizeof(char));
    ClearBuffer(buffer);
    wptr = 0;
    UartOnMsg = 0;
}