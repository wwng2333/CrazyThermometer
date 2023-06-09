#include "Delay.h"

void Delay50ms()		//@11.0592MHz
{
	unsigned char i, j, k;

	i = 3;
	j = 207;
	k = 28;
	do
	{
		do
		{
			while (--k);
		} while (--j);
	} while (--i);
}

void Delay70us()		//@11.0592MHz
{
	unsigned char i, j;

	i = 2;
	j = 2;
	do
	{
		while (--j);
	} while (--i);
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

void Delay2us()		//@11.0592MHz
{
	unsigned char i;

	_nop_();
	i = 5;
	while (--i);
}

void Delay12us()		//@11.0592MHz
{
	unsigned char i;

	_nop_();
	i = 42;
	while (--i);
}
