#include "STC8H.h"
#include "UART.h"
#include "DigitLED.h"
#include "DS18B20.h"
#include "TouchKey.h"
#include "Timer.h"
#include "ADC.h"
#include "IIC.h"

bit Timer2_Act = 0;
bit ADC_Finished = 0;

void main(void)
{
    UartInit();
    IIC_Init();
    //ADC_Init();
    DigitLED_Init();
    TK_Init();
    DS18B20_UART_InitReport();
    Timer2_Init();
    while (1)
    {
        if (Timer2_Act)
        {
            LM75_Update();
            //ADC_Update();
            TK2_Update();
            DS18B20_Update();
            Timer2_Act = ~Timer2_Act;
        }
    }
}