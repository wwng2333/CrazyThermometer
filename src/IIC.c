#include "IIC.h"
#include "UART.h"

//sbit SDA = P2^4;
//sbit SCL = P2^5;

unsigned int LM75_Update(void)
{
    unsigned int t = 0;
    IIC_Start();
    IIC_SendData(0x9E); //device addr+write, 1001 1110B
    IIC_RecvACK();
    IIC_SendData(0x00); //temperature
    IIC_RecvACK();

    IIC_Start();
    IIC_SendData(0x9F); //device addr+read, 1001 1111B
    IIC_RecvACK();
    t = IIC_RecvData();
    IIC_SendACK();
    t <<= 8;
    t = IIC_RecvData();
    IIC_SendNAK();
    IIC_Stop();
    return t;
}

void IIC_Init()
{
    P_SW2 |= 0x90;
    P2M0 = 0x30;
    P2M1 = 0x00;
    P_SW2 &= 0xDF;      // I2C P2.4/P2.5
    I2CCFG = 0xe0;      //使能I2C主机模式
    I2CMSST = 0x00;
    UartInitReport("LM75");
}

void IIC_Wait()
{
    while (!(I2CMSST & 0x40));
    I2CMSST &= ~0x40;
}

void IIC_Start()
{
    I2CMSCR = 0x01;     //发送START命令
    IIC_Wait();
}

void IIC_SendData(char dat)
{
    I2CTXD = dat;       //写数据到数据缓冲区
    I2CMSCR = 0x02;     //发送SEND命令
    IIC_Wait();
}

void IIC_RecvACK()
{
    I2CMSCR = 0x03;     //发送读ACK命令
    IIC_Wait();
}

char IIC_RecvData()
{
    I2CMSCR = 0x04;     //发送RECV命令
    IIC_Wait();
    return I2CRXD;
}

void IIC_SendACK()
{
    I2CMSST = 0x00;     //设置ACK信号
    I2CMSCR = 0x05;     //发送ACK命令
    IIC_Wait();
}

void IIC_SendNAK()
{
    I2CMSST = 0x01;     //设置NAK信号
    I2CMSCR = 0x05;     //发送ACK命令
    IIC_Wait();
}

void IIC_Stop()
{
    I2CMSCR = 0x06;     //发送STOP命令
    IIC_Wait();
}

