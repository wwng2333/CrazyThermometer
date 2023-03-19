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

sbit CPWM = P1^0;

void main(void)
{
    P1M0 |= 0x01; P1M1 &= ~0x01; //P1.0 Push-pull
    CPWM = 1; //Enable MOS Q1

    UartInit();
    //IIC_Init();
    //ADC_Init();
    DigitLED_Init(0x07); // LED 12.5% duty cycle
    //TK_Init();
    DS18B20_UART_InitReport();
    Timer2_Init();
    IAP_SetBright();
    while (1)
    {
        if(OnMessage) 
            UartOnMessage();
        if(Timer2_Act > 100) {
            //LM75_Update(0);
            DS18B20_Update(1);
            Timer2_Act = 0;
        } else {
            //TK2_Update();
        }
    }
}
