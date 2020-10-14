#include "led.h"

void LED_Init()  //�⺯������
{
	GPIO_InitTypeDef GPIO_InitStruct;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE|RCC_APB2Periph_GPIOB,ENABLE);

	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_InitStruct.GPIO_Pin=GPIO_Pin_5;
	GPIO_InitStruct.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOE,&GPIO_InitStruct);
	GPIO_SetBits(GPIOE,GPIO_Pin_5);  //��IO�ڳ�ʼ��Ϊ�ߵ�ƽ
	
	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_InitStruct.GPIO_Pin=GPIO_Pin_5;
	GPIO_InitStruct.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStruct);
	GPIO_SetBits(GPIOB,GPIO_Pin_5);  //��IO�ڳ�ʼ��Ϊ�ߵ�ƽ
}

void LED_Init2()  //�Ĵ�������
{
	/*CRL�˿ڵ�8λ�Ĵ���*/
	/*ODR�˿�����Ĵ���*/
  RCC->APB2ENR|=1<<3;  //����Bʱ��
	RCC->APB2ENR|=1<<6;  //����Eʱ��
	
	GPIOB->CRL&=0xFF0FFFFF; //���[23:20]��λ
	GPIOB->CRL|=0x00300000; //���ó�ͨ���������,����ٶ�Ϊ50MHz
	GPIOB->ODR|=1<<5;      //��PB5�˿�����ߵ�ƽ
	
  GPIOE->CRL&=0xFF0FFFFF; //���[23:20]��λ
	GPIOE->CRL|=0x00300000; //���ó�ͨ���������,����ٶ�Ϊ50MHz
	GPIOE->ODR|=1<<5;   //��PE5�˿�����ߵ�ƽ
}
