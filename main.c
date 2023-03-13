#include "STC8H.h"
#include "UART.h"
#include "Delay.h"
#include "DigitLED.h"
#include "DS18B20.h"

int main(void)
{
    int i;
    DS18B20_Init();
    DigitLED_Init();
    UartInit();

    UartSendStr("UART0: init ok!\r\n");
    DS18B20_UART_InitReport();

    while (1)
    {
        for (i = 0; i < 999; i++)
        {
            DigitLED_EnableDP(i);
            DS18B20_UART0_Debug();
            DigitLED_Write(i);
            Delay500ms();
        }
    }
}