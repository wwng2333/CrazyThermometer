#include "STC8H.h"
#include "UART.h"
#include "Delay.h"
#include "DigitLED.h"
#include "DS18B20.h"

int main(void)
{
    unsigned int Temp_Buffer = 0;
    int i;
    DigitLED_Init();
    UartInit();
    UartSendStr("Uart Test !\r\n");
    while (1)
    {
        for (i = 0; i < 999; i++)
        {
            DigitLED_Write(i);
            Temp_Buffer = Get_temp();
            if (flag_temper == 1)
            {
                UartSend('-');
            }
            if (Temp_Buffer / 1000 != 0) // 如果第一位为0，忽略显示
            {
                UartSend(Temp_Buffer / 1000 + '0'); // 显示温度百位
            }
            UartSend(Temp_Buffer % 1000 / 100 + '0'); // 显示温度十位值
            UartSend(Temp_Buffer % 100 / 10 + '0');   // 显示温度个位值
            UartSend('.');                            // 显示小数点
            UartSend(Temp_Buffer % 10 + '0');         // 显示温度十分位
            UartSendStr("C\r\n");
            Delay500ms();
        }
    }
}