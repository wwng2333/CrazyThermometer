#include "STC8H.h"
#include "UART.h"
#include "DigitLED.h"

int main(void)
{
    DigitLED_Init();
    UartInit();
    UartSendStr("Uart Test !\r\n");
    while(1);
}