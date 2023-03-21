#include "STC8H.h"
#include "UART.h"
#include "DigitLED.h"
#include "DS18B20.h"
#include "TouchKey.h"
#include "Timer.h"
//#include "ADC.h"
#include "IIC.h"
#include "IAP.h"
#include "PWM.h"

extern int Timer2_Act, SensorEnableCount = 0;
extern bit OnMessage, SendTemp;

void main(void)
{
    UartInit();
    IIC_Init();
    //ADC_Init();
    DigitLED_Init(0x07); // LED 12.5% duty cycle
    PWM_Init();
    //TK_Init();
    DS18B20_Init();
    Timer2_Init();
    IAP_SetBright();
    while (1)
    {
        if(OnMessage) 
            UartOnMessage();
        if(Timer2_Act > 100) {
            LM75_Update(0);
            DS18B20_Update(1);
            Timer2_Act = 0;
        } else {
            //TK2_Update();
        }
    }
}
