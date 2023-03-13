#include "STC8H.h"
#include "UART.h"
#include "Delay.h"
#include "DigitLED.h"
#include "DS18B20.h"
#include "TouchKey.h"

int main(void)
{
    UartInit();
    DigitLED_Init();
    TK_Init();
    DS18B20_UART_InitReport();

    /*
    P1DR = 0;
    P1SR = 0;
    //P1M0 &= 0xEF;
    P1M0 |= 0x10;
    P1M1 |= 0x10;
    P_SW2 |= 0x80;
    PWMA_PS = 0x30;
    PWMA_CCER1 = 0x00;
    PWMA_CCMR1 = 0x60;
    PWMA_CCER1 = 0x01;
    PWMA_CCR1 = 100;
    PWMA_ARR = 500;
    PWMA_ENO |= 0x10; //Enable PWM1P
    PWMA_BKR = 0x80;
    PWMA_CR1 = 0x01;
*/   

    while (1)
    {
        UartSend(TK2_Read());
        //DS18B20_UART0_Debug();
        DigitLED_Write(DS18B20_GetTemp());
        Delay50ms();
    }
}