#include <reg51.h>

sbit ledpin = P1^2;

void delay()
{
    int i;

    for(i = 0; i < 1; i++)
    {
    }
}

void main()
{
    while(1)
    {
        ledpin = 0;
        delay();

        ledpin = 1;
        delay();
    }
}
