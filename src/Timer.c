#include "Timer.h"
#include "UART.h"

extern volatile int Timer2Counter = 0;

void Timer2_Init(void)      //500毫秒@11.0592MHz
{
    P_SW2 |= 0x80;
	AUXR |= 0x04;			//定时器时钟1T模式
	T2L = 0xE2;				//设置定时初始值
	T2H = 0x01;				//设置定时初始值
	AUXR |= 0x10;			//定时器2开始计时
	IE2 |= 0x04;			//使能定时器2中断
    EA = 1;
    P_SW2 &= ~0x80;
    UartInitReport("Timer2");
}

void Timer2_Isr(void) interrupt 12
{
    Timer2Counter++;
}