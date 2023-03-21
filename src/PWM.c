#include "PWM.h"
#include "UART.h"

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
    PWMA_CCR1 = 100;
    PWMA_ARR = 500;
    PWMA_BKR = 0x80;
    PWMA_CR1 = 0x01;
}