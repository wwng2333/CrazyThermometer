#include "ADC.h"
#include "UART.h"

void ADC_Init(void)
{
    P_SW2 |= 0x80;
    P1M0 = 0x00;        //P1.6 高阻输入
    P1M1 = 0x40;
    P_SW2 |= 0x80;
    ADCTIM = 0x3f;      //设置ADC内部时序
    P_SW2 &= 0x7f;
    ADCCFG = 0x0f;      //设置ADC时钟为系统时钟/2/16
    ADC_CONTR = 0x80;   //使能ADC模块
    EADC = 1;           //使能ADC中断
    EA = 1;
    ADC_CONTR |= 0x40;  //启动AD转换
    P_SW2 &= ~0x80;
    UartInitReport("ADC");
}