#include "IIC.h"
#include "UART.h"
#include "Delay.h"
#include "DigitLED.h"
#include "stdio.h"

//sbit SDA = P2^4;
//sbit SCL = P2^5;
bit LM75_Busy = 0;
unsigned int LM75_old = 0;

void I2C_Isr() interrupt 24
{
    if (I2CMSST & 0x40)
    {
        I2CMSST &= ~0x40; //清中断标志
        LM75_Busy = 0;
    }
}

void LM75_Update()
{
    extern unsigned int LM75_old;
    unsigned int now;
    now = LM75_GetTemp();
    if(now != LM75_old)
    {
        LM75_old = now;
        //UartSendStr("LM75: ");
        //if (LM75_old / 1000 != 0)
            //UartSend(LM75_old / 1000 + '0');
        //UartSend(LM75_old % 1000 / 100 + '0');
        //UartSend(LM75_old % 100 / 10 + '0');
        //UartSend('.');
        //UartSend(LM75_old % 10 + '0');
        //UartSendStr("C\r\n");
        DigitLED_Write(LM75_old);
    }
}

unsigned int LM75_GetTemp(void)
{
    unsigned int t = 0;
    IIC_Start();
    IIC_SendData(0x9E); //device addr+write, 1001 1110B
    IIC_RecvACK();
    IIC_SendData(0x00); //temperature
    IIC_RecvACK();
    Delay30us();
    IIC_Start();
    IIC_SendData(0x9F); //device addr+read, 1001 1111B
    IIC_RecvACK();
    t = IIC_RecvData() << 8;
    IIC_SendACK();
    t += IIC_RecvData();
    IIC_SendNAK();
    IIC_Stop();
    t >>= 5;
    UartSend(t);
    return t;
}

void IIC_Init()
{
    P_SW2 = 0x90;       // I2C P2.4/P2.5
    P2M0 |= 0x30;
    P2M1 |= 0x30; 
    I2CCFG = 0xe0;      //使能I2C主机模式
    I2CMSST = 0x00;
    UartInitReport("LM75");
}

/*
void IIC_Wait()
{
    while (!(I2CMSST & 0x40));
    I2CMSST &= ~0x40;
}
*/

void IIC_Start()
{
    while (LM75_Busy);
    LM75_Busy = 1;
    P_SW2 |= 0x80;
    I2CMSCR = 0x81;     //发送START命令
    while (LM75_Busy);
}

void IIC_SendData(char dat)
{
    LM75_Busy = 1;
    I2CTXD = dat;       //写数据到数据缓冲区
    I2CMSCR = 0x82;     //发送SEND命令
    while (LM75_Busy);
}

void IIC_RecvACK()
{
    LM75_Busy = 1;
    I2CMSCR = 0x83;     //发送读ACK命令
    while (LM75_Busy);
}

char IIC_RecvData()
{
    LM75_Busy = 1;
    I2CMSCR = 0x84;     //发送RECV命令
    while (LM75_Busy);
    return I2CRXD;
}

void IIC_SendACK()
{
    LM75_Busy = 1;
    I2CMSST = 0x00;     //设置ACK信号
    I2CMSCR = 0x85;     //发送ACK命令
    while (LM75_Busy);
}

void IIC_SendNAK()
{
    LM75_Busy = 1;
    I2CMSST = 0x01;     //设置NAK信号
    I2CMSCR = 0x85;     //发送ACK命令
    while (LM75_Busy);
}

void IIC_Stop()
{
    LM75_Busy = 1;
    I2CMSCR = 0x86;     //发送STOP命令
    while (LM75_Busy);
    P_SW2 &= ~0x80; 
}

