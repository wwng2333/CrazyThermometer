#include "STC8H.h"
#include "UART.h"
#include "Delay.h"
#include "DigitLED.h"
#include "DS18B20.h"

unsigned int key_data;
unsigned char dat_H,dat_L;

unsigned int Read_Key_value(void);

int main(void)
{
    P_SW2 |= 0x80;
    P5M0 |= 0x00;
    P5M1 |= 0x00;
    TSCHEN1 = 0x04;
    TSCHEN2 = 0x00;
    TSRT = 0x01;
    TSCFG1 = 0x70;
    TSCFG2 = 0x00;
    TSCTRL = 0x80;
    P_SW2 &= ~0x80;

    DigitLED_Init();
    UartInit();
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
        UartSend(0xFF);
        UartSend(Read_Key_value());
        //DS18B20_UART0_Debug();
        DigitLED_Write(DS18B20_GetTemp());
        Delay500ms();
    }
}

unsigned int Read_Key_value(void)
{
    unsigned char j;
    unsigned int i,ret;
    P_SW2 |= 0x80;
    for(i=0;i<100;i++)
    {
        j = TSSTA2;
        if(j & 0x40)
        {
            TSSTA2 |= 0x40;
            ret = 0xee;
        }

        if(j & 0x80)
        {
            TSSTA2 |= 0x80;
            ret = TSDAT;
        }
    }
    P_SW2 &= ~0x80;
    return ret;
}