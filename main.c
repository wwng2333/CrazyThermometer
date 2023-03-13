#include "STC8H.h"
#include "UART.h"
#include "Delay.h"
#include "DigitLED.h"
#include "DS18B20.h"

int main(void)
{
    unsigned int Temp_Buffer = 0;
    int i;
    DigitLED_Init();
    UartInit();

    P2M0 |= 0x08;
    P2M1 |= 0x08;

    UartSendStr("Uart Test !\r\n");
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