#ifndef __DIGIT_LED_H__
#define __DIGIT_LED_H__

void DigitLED_Init(unsigned char dat);
void DigitLED_Write(unsigned int dat);
void DigitLED_EnableDP(int dat);
void DigitLED_Duty(unsigned int dat);
#endif