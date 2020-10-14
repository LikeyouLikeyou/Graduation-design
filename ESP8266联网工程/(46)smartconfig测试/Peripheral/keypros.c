#include "keypros.h"

void key_pros_Init()  //������ʼ������
{
	GPIO_InitTypeDef GPIO_InitStruct;
	SystemInit();
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOE,ENABLE);
	
	/* �̵� */
	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_IPD; //����Ϊ��������
	GPIO_InitStruct.GPIO_Pin=GPIO_Pin_0;
	GPIO_InitStruct.GPIO_Speed= GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStruct);
	
	/* ��� */
	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_IPU;  //����Ϊ��������
	GPIO_InitStruct.GPIO_Pin=GPIO_Pin_4|GPIO_Pin_3|GPIO_Pin_2;
	GPIO_InitStruct.GPIO_Speed= GPIO_Speed_50MHz;
	GPIO_Init(GPIOE,&GPIO_InitStruct);
}

u8 key_scan(u8 mode)
{
	static u8 key=1;  //ֻ��ִ��һ��
	if(mode==1)   //�ж��Ƿ�֧������,mode=1��֧������
		key =1;
	if(key&&(key_0==0||key_1==0||key_2==0||key_wk_up==1))  //����ĸ�������һ������
	{
		delay_ms(10);
		key=0;
		if(key_0==0)   //�������0����
		{
			return key_0_press;  //�򷵻����ֵ2
		}
		else if(key_1==0)  //�������1����
		{
			return key_1_press;  //�򷵻����ֵ3
		}
		else if(key_2==0)  //�������2����
		{
			return key_2_press;  //�򷵻����ֵ4
		}
		else if(key_wk_up==1)  //�������wk_up����
		{
			return key_wk_up_press;   //�򷵻����ֵ1
		}
	 }else if(key_0==1&&key_1==1&&key_2==1&&key_wk_up==0)   //�������û�а�������
	  { 
		  key=1;
	  }
	  return 0; //���key=0(Ҳ�ͻ�֧������)ʱ��һ��ifΪ��,û�а�������ʱ�ڶ���ifҲΪ�ٴ�ʱ����0,�������κβ���
}
