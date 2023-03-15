#include "DS18B20.h"
#include "Delay.h"
#include "UART.h"

unsigned char flag_temper = 0;

void DS18B20_UART_InitReport()
{
    switch(DS18B20_CheckDevice())
    {
        case 0: 
            UartInitReport("18B20");
            break;
        case 1: 
            UartInitReport("18B20^1");
            //UartSendStr("18B20: NO ACK!\r\n");
            break;
        case 2: 
            UartInitReport("18B20^2");
            //UartSendStr("18B20: release failed!\r\n");
            break;
    }
}

void DS18B20_UART0_Debug()
{
    unsigned int Temp_Buffer = 0;
    Temp_Buffer = DS18B20_GetTemp();
    UartSendStr("18B20: ");
    if (flag_temper == 1)
        UartSend('-');
    if (Temp_Buffer / 1000 != 0)
        UartSend(Temp_Buffer / 1000 + '0');
    UartSend(Temp_Buffer % 1000 / 100 + '0');
    UartSend(Temp_Buffer % 100 / 10 + '0');
    UartSend('.');
    UartSend(Temp_Buffer % 10 + '0');
    UartSendStr("C\r\n");
}

unsigned int DS18B20_CheckDevice(void)
{
    DS18B20_Reset();
    return DS18B20_WaitReady();
}

void DS18B20_Write_Byte(unsigned char dat)
{
    unsigned char i;
    for (i = 0; i < 8; i++)
    {
        DS18B20_Write_Bit(dat & 0x01);
        dat >>= 1;
    }
}

void DS18B20_Write_Bit(bit dat)
{
    DS18B20_DQ = 0;
    Delay2us();
    DS18B20_DQ = dat;
    Delay70us();
    DS18B20_DQ = 1;
    Delay2us();
}

bit DS18B20_Read_Bit()
{
    bit dat;
    DS18B20_DQ = 0;
    Delay2us();
    DS18B20_DQ = 1;
    Delay12us();
    if(DS18B20_DQ) dat = 1;
    else dat = 0;
    Delay70us();
    return dat;
}

unsigned char DS18B20_Read_Byte()
{
    unsigned char i, dat;
    for (i = 0; i < 8; i++)
    {
        dat >>= 1;
        if(DS18B20_Read_Bit()) dat |= 0x80;
    }
    return dat;
}

void DS18B20_Init()
{
    P_SW2 |= 0x80;
    P2M0 |= 0x08;
    P2M1 |= 0x08;
    P_SW2 &= ~0x80;
}

void DS18B20_Reset()
{    
    DS18B20_DQ = 1; // 释放总线
    Delay2us();

    DS18B20_DQ = 0;
    Delay500us(); // 延时480~960us

    DS18B20_DQ = 1;    // 释放总线
    Delay30us(); // 延时15~60us
}

unsigned int DS18B20_WaitReady(void)
{
    unsigned int count = 0;
    DS18B20_Init();
    while((DS18B20_DQ == 1) && (count < 240))
    {
        Delay2us();
        count++;
    }
    if(count > 240) return 1;
    else count = 0;
    while((DS18B20_DQ == 0) && (count < 240))
    {
        Delay2us();
        count++;
    }
    return (count > 240) ? 2 : 0;
}

//**********************************************************
// 读取温度函数，返回温度的绝对值，并标注flag_temper，flag_temper=1表示负，flag_temper=0表示正
//**********************************************************
unsigned int DS18B20_GetTemp(void) // 读取温度值
{
    float tt;
    unsigned char a, b;
    unsigned int temp;
    //while(!DS18B20_DQ); //wait 18b20 ready
    if (DS18B20_CheckDevice() == 0) // 初始化
    {
        DS18B20_Write_Byte(0xcc); // 忽略ROM指令
        DS18B20_Write_Byte(0x44); // 温度转换指令

        //Delay500ms();				//PROTEUS仿真需要加

        if (DS18B20_CheckDevice() == 0) // 初始化
        {
            DS18B20_Write_Byte(0xcc); // 忽略ROM指令
            DS18B20_Write_Byte(0xbe); // 读暂存器指令
            a = DS18B20_Read_Byte();  // 读取到的第一个字节为温度LSB
            b = DS18B20_Read_Byte();  // 读取到的第一个字节为温度MSB
            temp = b;                 // 先把高八位有效数据赋于temp
            temp <<= 8;               // 把以上8位数据从temp低八位移到高八位
            temp = temp | a;          // 两字节合成一个整型变量

            if (temp > 0xfff)
            {
                flag_temper = 1; // 温度为负数
                temp = (~temp) + 1;
            }
            else
            {
                flag_temper = 0; // 温度为正或者0
            }

            tt = temp * 0.0625;   // 得到真实十进制温度值
                                  // 因为DS18B20可以精确到0.0625度
                                  // 所以读回数据的最低位代表的是0.0625度
            temp = tt * 10 + 0.5; // 放大十倍
                                  // 这样做的目的将小数点后第一位也转换为可显示数字
                                  // 同时进行一个四舍五入操作。
        }
    }
    return temp;
}
