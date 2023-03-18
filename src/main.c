#include "STC8H.h"
#include "UART.h"
#include "DigitLED.h"
#include "DS18B20.h"
#include "TouchKey.h"
#include "Timer.h"
//#include "ADC.h"
#include "IIC.h"
#include "IAP.h"

extern int Timer2_Act;
extern bit OnMessage, SendTemp;

void main(void)
{
    UartInit();
    IIC_Init();
    //ADC_Init();
    DigitLED_Init();
    TK_Init();
    DS18B20_UART_InitReport();
    Timer2_Init();
    IAP_SetBright();
    while (1)
    {
        if(OnMessage) 
        {
            UartOnMessage();
        } else if(Timer2_Act > 128) {
            //TK2_Update();
            LM75_Update(1);
            DS18B20_Update(0);
        }
    }
}