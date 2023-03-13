#include "STC8H.h"
#include "UART.h"
#include "Delay.h"
#include "DigitLED.h"
#include "DS18B20.h"

int main(void)
{
    unsigned int Temp_Buffer = 0;
    int i;
    DS18B20_Init();
    DigitLED_Init();
    UartInit();
    //P_SW2 |= 0x80;
    //P2PU |= 0x08;

    UartSendStr("Uart Test !\r\n");

    switch(DS18B20_CheckDevice())
    {
        case 0: 
            UartSendStr("18B20: Init OK!\r\n");
            break;
        case 1: 
            UartSendStr("18B20: NO ACK!\r\n");
            break;
        case 2: 
            UartSendStr("18B20: release failed!\r\n");
            break;
    }
    while (1)
    {
        for (i = 0; i < 999; i++)
        {
            DigitLED_Write(i);
            Temp_Buffer = Get_temp();
            if (flag_temper == 1)
                UartSend('-');
            if (Temp_Buffer / 1000 != 0)
                UartSend(Temp_Buffer / 1000 + '0');
            UartSend(Temp_Buffer % 1000 / 100 + '0');
            UartSend(Temp_Buffer % 100 / 10 + '0');
            UartSend('.');
            UartSend(Temp_Buffer % 10 + '0');
            UartSendStr("C\r\n");
            Delay500ms();
        }
    }
}