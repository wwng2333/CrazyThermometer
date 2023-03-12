#include "STC8H.h"
#include "UART.h"
#include "DigitLED.h"
#include "intrins.h"

void Delay500ms() //@11.0592MHz
{
    unsigned char i, j, k;

    i = 29;
    j = 14;
    k = 54;
    do
    {
        do
        {
            while (--k)
                ;
        } while (--j);
    } while (--i);
}

int main(void)
{
    int i;
    DigitLED_Init();
    UartInit();
    UartSendStr("Uart Test !\r\n");
    while (1)
    {
        for (i = 0; i < 999; i++)
        {
            DigitLED_Write(i);
            Delay500ms();
        }
    }
}