#include "STC8H.h"
#include "UART.h"

int main(void)
{
    UartInit();
    ES = 1;
    EA = 1;
    UartSendStr("Uart Test !\r\n");
    while(1);
}