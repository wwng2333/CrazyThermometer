#include "STC8H.h"
#include "DigitLED.h"

char code digit[10] = {
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

void DigitLED_Init(void)
{
    P_SW2 |= 0x80;
    COMEN = 0x83;
    SEGENH = 0xFF;
    LEDCKS = 7;
    LEDCTRL = 0x80;
}

void DigitLED_COM0_Write(int dat)
{
    COM0_DC_H = digit[dat];
}

void DigitLED_COM1_Write(int dat)
{
    COM1_DC_H = digit[dat];
}

void DigitLED_COM7_Write(int dat)
{
    COM7_DC_H = digit[dat];
}