#include "delay.h"

void delay_us(u32 i)  //延时微秒
{
	u32 temp;
	SysTick->LOAD=9*i;
	SysTick->CTRL=0x01;
	SysTick->VAL=0;
	do
	{
		temp=SysTick->CTRL;
	}
	while((temp&0x01)&&(!(temp&(1<<16))));
	SysTick->CTRL=0;
	SysTick->VAL=0;
}

/* 这里的i<=1864 */
void delay_ms(u32 i)   //延时毫秒
{
	u32 temp;
	SysTick->LOAD=9000*i;
	SysTick->CTRL=0x01;
	SysTick->VAL=0;
	do
	{
		temp=SysTick->CTRL;
	}
	while((temp&0x01)&&(!(temp&(1<<16))));
	SysTick->CTRL=0;
	SysTick->VAL=0;
}
