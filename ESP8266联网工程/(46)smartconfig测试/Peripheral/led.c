#include "led.h"

void LED_Init()  //库函数控制
{
	GPIO_InitTypeDef GPIO_InitStruct;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE|RCC_APB2Periph_GPIOB,ENABLE);

	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_InitStruct.GPIO_Pin=GPIO_Pin_5;
	GPIO_InitStruct.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOE,&GPIO_InitStruct);
	GPIO_SetBits(GPIOE,GPIO_Pin_5);  //将IO口初始化为高电平
	
	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_InitStruct.GPIO_Pin=GPIO_Pin_5;
	GPIO_InitStruct.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStruct);
	GPIO_SetBits(GPIOB,GPIO_Pin_5);  //将IO口初始化为高电平
}

void LED_Init2()  //寄存器控制
{
	/*CRL端口低8位寄存器*/
	/*ODR端口输出寄存器*/
  RCC->APB2ENR|=1<<3;  //开启B时钟
	RCC->APB2ENR|=1<<6;  //开启E时钟
	
	GPIOB->CRL&=0xFF0FFFFF; //清除[23:20]四位
	GPIOB->CRL|=0x00300000; //配置成通用推挽输出,最大速度为50MHz
	GPIOB->ODR|=1<<5;      //让PB5端口输出高电平
	
  GPIOE->CRL&=0xFF0FFFFF; //清除[23:20]四位
	GPIOE->CRL|=0x00300000; //配置成通用推挽输出,最大速度为50MHz
	GPIOE->ODR|=1<<5;   //让PE5端口输出高电平
}
