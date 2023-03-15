#include "STC8H.h"
#include "UART.h"
#include "DigitLED.h"
#include "DS18B20.h"
#include "TouchKey.h"
#include "Timer.h"

bit Timer2_Act = 0;

int main(void)
{
    UartInit();
    DigitLED_Init();
    TK_Init();
    DS18B20_UART_InitReport();
    Timer2_Init();
    while (1)
    {
        if (Timer2_Act)
        {
            DS18B20_UART0_Debug();
            DigitLED_Write(DS18B20_GetTemp());
            Timer2_Act = 0;
        }
    }
}