#include "PWM.h"
#include "UART.h"
#include "Delay.h"

int PwmNow = 0;
bit PwmRise = 1;

void PWM_Init(void)
{
    P_SW2 |= 0x80;
    P1M0 |= 0x01;
    P1M1 &= ~0x01; //P1.0 Push-pull
    PWMA_PS = 0x00;
    PWMA_ENO |= 0x01; //Enable PWM1P
    PWMA_CCER1 = 0x00;
    PWMA_CCMR1 = 0x60;
    PWMA_CCER1 = 0x01;
    PWMA_CCR1 = PwmNow;    //设置占空比时间
    PWMA_ARR = 500;     //设置周期时间
    PWMA_BKR = 0x80;
    PWMA_CR1 = 0x01;
}

void PWM_Update(void)
{
    if(PwmRise) 
    {
        PwmNow += 5;
        if(PwmNow >= 200) PwmRise = 0;
    } else {
        PwmNow -= 5;
        if(PwmNow <= 10) PwmRise = 1;
    }
    UartSendStr("PWM: ");
    if (PwmNow / 1000 != 0)
        UartSend(PwmNow / 1000 + '0');
    UartSend(PwmNow % 1000 / 100 + '0');
    UartSend(PwmNow % 100 / 10 + '0');
    P_SW2 |= 0x80;
    PWMA_CCR1 = PwmNow;
    Delay50ms();
}