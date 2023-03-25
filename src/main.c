#include "main.h"

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
        PWM_Update();
        if(UartOnMsg)               //串口收到消息
        {
            UartOnMessage();        //处理消息
            LM75_Update(0);         //LM75响应请求
            DS18B20_Update(0);      //18B20响应请求
        }
        if(Timer2Counter > 100) {   //定时器触发
            LM75_Update(1);         //LM75处理函数，数码管不显示
            DS18B20_Update(0);      //18B20处理函数，数码管显示其温度
            Timer2Counter = 0;      //清除标志
        } else {                    //空闲
            //TK2_Update();         //处理按键
        }
    }
}
