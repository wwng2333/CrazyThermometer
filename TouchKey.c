#include "STC8H.h"
#include "TouchKey.h"
#include "UART.h"

void TK_Init()
{
    P_SW2 |= 0x80;
    P5M0 |= 0x00;
    P5M1 |= 0x00;
    TSCHEN1 = 0x04;
    TSCHEN2 = 0x00;
    TSRT = 0x01;
    TSCFG1 = 0x70;
    TSCFG2 = 0x00;
    TSCTRL = 0x80;
    P_SW2 &= ~0x80;
    UartInitReport("TK");
}

bit TK2_Read(void)
{
    unsigned char j;
    unsigned int i;
    bit ret;
    P_SW2 |= 0x80;
    for(i=0;i<100;i++)
    {
        j = TSSTA2;
        if(j & 0x40)
        {
            TSSTA2 |= 0x40;
            ret = 0xee;
        }
        if(j & 0x80)
        {
            TSSTA2 |= 0x80;
            ret = TSDAT;
        }
    }
    P_SW2 &= ~0x80;
    return ret;
}