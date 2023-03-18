#include "ADC.h"
#include "UART.h"
#include "Delay.h"
#include "DigitLED.h"
#include <stdio.h>
/*
#define CPUIDBASE 0xfde0
#define VREF_ADDR (*(unsigned int volatile xdata *)(CPUIDBASE + 0x07))

bit adcold = 0;

void ADC_Init()
{
    P_SW2 |= 0x80;
    P1M0 = 0x00;        //P1.6 高阻输入
    P1M1 = 0x40;
    ADCTIM = 0x3f;           //设置ADC内部时序
    P_SW2 &= 0x7f;

    ADCCFG = 0x2f;           //设置ADC时钟为系统时钟/2/16
    //ADC_CONTR = 0x8f;       //使能ADC模块,并选择第15通道
    ADC_CONTR = 0x86;       //使能ADC模块,并选择第6通道
}

int ADC_Read()
{
    int res;

    ADC_CONTR |= 0x40;  //启动AD转换
    _nop_();
    _nop_();
    while (!(ADC_CONTR & 0x20));                //查询ADC完成标志
    ADC_CONTR &= ~0x20;                         //清完成标志
    res = (ADC_RES << 8) | ADC_RESL;            //读取ADC结果

    return res;
}

void ADC_Update(void)
{
    extern bit adcold;
    bit adcnew;
    int vcc,i;
    for(i=0;i<8;i++) vcc += ADC_Read();
    vcc >>= 3;
    vcc = (int)(1024L*VREF_ADDR / vcc);
    adcnew = (vcc > 0) ? 0 : 1; //12.5%
    if(adcnew != adcold) {
        adcold = adcnew;
        //if(vcc > 0) DigitLED_Duty(0x07);
        //else DigitLED_Duty(0x04); //100%
    }
}

int ADC_Read(void)
{
    int *BGV;
    int res;
    *BGV = (int idata *)0xef;
    res = (ADC_RES << 8) | ADC_RESL;
    //return (int)(1024L * *BGV / res);
    return res;
}


void ADC_Isr() interrupt 5
{
    extern bit ADC_Finished;
    P_SW2 |= 0x80;
    ADC_CONTR &= ~0x20;     //清中断标志
    //P2 = ADC_RES;           //读取ADC结果
    //ADC_CONTR |= 0x40;      //继续AD转换
    P_SW2 &= ~0x80;
    ADC_Finished = 1;
}

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
*/