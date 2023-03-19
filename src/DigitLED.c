#include "STC8H.h"
#include "DigitLED.h"
#include "UART.h"
#include "stdio.h"

static char code digit[10] = {
    0xAF,
    0x28,
    0x9B,
    0xBA,
    0x3C,
    0xB6,
    0xB7,
    0x2A,
    0xBF,
    0xBE,
};

void DigitLED_Init(unsigned char dat)
{
    P_SW2 |= 0x80;
    COMEN = 0x83;
    SEGENH = 0xFF;
    LEDCKS = 0x1E;
    LEDCTRL = 0x80;
    LEDCTRL |= dat; //12.5%
    P_SW2 &= ~0x80; 
    UartInitReport("Digit");
}

void DigitLED_EnableDP(int dat)
{
    P_SW2 |= 0x80;
    switch(dat)
    {
        case 0: 
            COM7_DC_H |= 0x40; 
            break;
        case 1:
            COM0_DC_H |= 0x40; 
            break;
        case 2:
            COM1_DC_H |= 0x40; 
            break;
    }
    P_SW2 &= ~0x80;
}

void DigitLED_Write(unsigned int dat)
{
    P_SW2 |= 0x80;
    if(dat >= 100) COM7_DC_H = digit[dat / 100];
    if(dat >= 10) COM0_DC_H = digit[dat / 10 % 10];
    COM1_DC_H = digit[dat % 10];
    DigitLED_EnableDP(1);
    P_SW2 &= ~0x80; 
}

void DigitLED_Duty(unsigned int dat)
{
    P_SW2 |= 0x80;
    LEDCTRL = 0x80 | dat;
    P_SW2 &= ~0x80; 
    UartSend(dat);
    //printf("LED duty %d\n", dat);
}