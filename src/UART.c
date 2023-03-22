#include "UART.h"
#include "string.h"
#include "stdio.h"
#include "IAP.h"

bit busy;
char wptr;
char rptr;
char buffer[16];

bit UartOnMsg = 0;
unsigned int SendTemp = 0;
extern int SensorEnableCount;

char code *STCISPCMD = "@STCISP#";
char ISP_INDEX;

typedef enum
{
    TEMP,
    RST,
    IAPR,
    IAPW,
    NONE,
    _NULL,
} COMMAND;

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
        if (SBUF == STCISPCMD[ISP_INDEX])
        {
            ISP_INDEX++;
            if (STCISPCMD[ISP_INDEX] == '\0')
                IAP_CONTR = 0x60;
        } else {
            ISP_INDEX = 0;
            if (SBUF == STCISPCMD[ISP_INDEX])
                ISP_INDEX++;
        }
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

/*
char putchar(char ch)
{
    SBUF = ch;
    while(TI == 0);
    TI = 0;
    return ch;
}*/

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
    char cmd_dat[] = {0}, cmd_val = 0xa;
    int i, cmd_len;
    COMMAND cmd = _NULL;

    if(buffer[0] == 'A' && buffer[1] == 'T' && buffer[wptr-1] == '\n')
    {
        //收全一个数据包，开始处理
        if(buffer[2] == '+')
        {
            for(i=3; i<wptr; i++) //判断是否有=
            {
                if(buffer[i] == 0x3D)
                {
                    cmd_len = i;
                    cmd_val = buffer[i];
                    break;
                } else {
                    cmd_len = wptr;
                }
            }
            memcpy(cmd_dat, buffer+3, cmd_len); //提取AT+[..]=x
            UartSendStr(cmd_dat);
            //if(cmd_val != 0xaa) UartSend(cmd_len);
            //UartSendStr("\r\n");
            if(strcmp("TEMP", cmd_dat) <= 0) 
                cmd = TEMP;
            else if(strcmp("RST", cmd_dat) <= 0) 
                cmd = RST;
            else if(strcmp("IAPR", cmd_dat) <= 0) 
                cmd = IAPR;
            else if(strcmp("IAPW", cmd_dat) <= 0) 
                cmd = IAPW;
        } else {
            cmd = NONE;
        }

        ClearBuffer(buffer); //清buff
        wptr = 0;

        switch(cmd)
        {
        case TEMP:
            SendTemp = SensorEnableCount;
        break;
        case RST:
            P_SW2 |= 0x80;
            IAP_CONTR |= 0x20;
            break;
        case IAPR:
            IAP_ReadBright();
            break;
        case IAPW:
            IAP_SaveBright();
            break;
        case NONE:
            UartSendOK();
            break;
        default: 
            UartSendStr("ERROR\r\n");
        }
    }
    UartOnMsg = 0;
}