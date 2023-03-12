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

void DigitLED_Write(int dat)
{
    COM7_DC_H = digit[dat / 100];
    COM0_DC_H = digit[dat / 10 % 10];
    COM1_DC_H = digit[dat % 10];
}