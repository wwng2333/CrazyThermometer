#include "STC8H.h"
#include "UART.h"
#include "DigitLED.h"
#include "DS18B20.h"
#include "TouchKey.h"
#include "Timer.h"
//#include "ADC.h"
#include "IIC.h"

extern volatile int Timer2_Act = 0;

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
        TK2_Update();
        //UartSend(Timer2_Act);
        if (Timer2_Act > 100)
        {
            Timer2_Act = 0;
            LM75_Update();
            //ADC_Update();
            //DS18B20_Update();
        }
    }
}