#include "STC8H.h"
#include "UART.h"

int main(void)
{
    UartInit();
    UartSendStr("Uart Test !\r\n");
    while(1);
}