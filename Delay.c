#include "Delay.h"

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
