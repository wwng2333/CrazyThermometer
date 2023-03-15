#include "STC8H.h"
#include "UART.h"
#include "Delay.h"
#include "DigitLED.h"
#include "DS18B20.h"
#include "TouchKey.h"
#include "Timer.h"

int main(void)
{
    UartInit();
    DigitLED_Init();
    TK_Init();
    DS18B20_UART_InitReport();
    Timer2_Init();
    while (1);
}