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

extern int Timer2Counter;
extern int SensorEnableCount = 0;
extern int DigitLEDDuty = 0;
extern bit UartOnMsg, SendTemp;

void main(void)
{
    DigitLEDDuty = IAP_GetBright();
    UartInit();
    DS18B20_Init();
    IIC_Init();
    //ADC_Init();
    DigitLED_Init(DigitLEDDuty); // LED 12.5% duty cycle
    PWM_Init();
    //TK_Init();
    Timer2_Init();

    while (1)                       //主循环
    {
        if(UartOnMsg)               //串口收到消息
        {
            UartOnMessage();        //处理消息
            LM75_Update(0);         //LM75响应请求
            DS18B20_Update(0);      //18B20响应请求
        }
        if(Timer2Counter > 100) {   //定时器触发
            LM75_Update(0);         //LM75处理函数，数码管不显示
            DS18B20_Update(1);      //18B20处理函数，数码管显示其温度
            Timer2Counter = 0;      //清除标志
        } else {                    //空闲
            //TK2_Update();         //处理按键
        }
    }
}
