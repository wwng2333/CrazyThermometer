#include "Delay.h"
#include <intrins.h>

void Delay500ms() //@11.0592MHz
{
    unsigned char i, j, k;

    i = 29;
    j = 14;
    k = 54;
    do
    {
        do
        {
            while (--k)
                ;
        } while (--j);
    } while (--i);
}

void Delay70us()		//@11.0592MHz
{
	unsigned char i;

	i = 0;
	while (--i);
}

void Delay500us()		//@11.0592MHz
{
	unsigned char i, j;

	_nop_();
	_nop_();
	i = 8;
	j = 43;
	do
	{
		while (--j);
	} while (--i);
}

void Delay30us()		//@11.0592MHz
{
	unsigned char i;

	_nop_();
	_nop_();
	i = 108;
	while (--i);
}
