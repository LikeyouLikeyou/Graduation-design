#include "timer.h"
#include "usart3.h"
#include "mymqtt.h"
#include "printf.h"
#include "delay.h"

/**************************************************************
��������: Timer_init(u16 arr,u16 psc)
��������: ��ʼ����ʱ��
�������: 
          arr���Զ���װֵ��
          psc��ʱ��Ԥ��Ƶ��
			
˵����
     Tout(���ʱ��)=(ARR+1)(PSC+1)/Tclk
		 Tclk����ʱ��������ʱ��Ƶ�ʣ���λMHZ��Ҳ����CK_INTʱ��
		 Tout����ʱ�����ʱ�䣨��λΪs��
		 (psc+1))/Tclk*1�Ǽ���ļ���������һ�������õ�ʱ��(��λΪs)
		 ��ô(psc+1))/Tclk*5000����һ�ζ�ʱ����ʱ��

�� �� ֵ: ��
��    ע: ��
**************************************************************/
void Timer_init(u16 arr,u16 psc)                                      //��ʱ����ʼ������   ֮����������u16��������Ϊ�˴��ļĴ�����16λ��
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitstruct;
	NVIC_InitTypeDef NVIC_InitStruct;
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);                 //ʹ���ڲ�ʱ��(CK_INT)
  /* ��ʱ������ */
	TIM_TimeBaseInitstruct.TIM_Period=arr;                              //��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ
	TIM_TimeBaseInitstruct.TIM_Prescaler=psc;                           //����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ
  TIM_TimeBaseInitstruct.TIM_ClockDivision=TIM_CKD_DIV1;              //����ʱ�ӷָ�:TDTS=Tck_tim
	TIM_TimeBaseInitstruct.TIM_CounterMode=TIM_CounterMode_Up;          //���ϼ���ģʽ

	TIM_TimeBaseInit(TIM3,&TIM_TimeBaseInitstruct);                     //��ʼ��ʱ�������λ ��
	
	TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE);                            //ʹ�ܶ�ʱ��3�����ж�
	
	/*�ж����ȼ�����*/
	NVIC_InitStruct.NVIC_IRQChannel=TIM3_IRQn;                          //��ʱ��3ȫ���ж�ͨ��
	NVIC_InitStruct.NVIC_IRQChannelCmd=ENABLE;                          //ʹ��IRQͨ��
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority=0;                //��ռ���ȼ�
	NVIC_InitStruct.NVIC_IRQChannelSubPriority=0;                       //��Ӧ���ȼ�
  NVIC_Init(&NVIC_InitStruct);
	
	TIM_Cmd(TIM3,ENABLE);                                               //ʹ�ܶ�ʱ��3
}


u8 lenght,nms;
u8 package[2]={0};                              //������������
u8 ping[2]={0xc0,0x00};                         //������У��


void TIM3_IRQHandler()                          //��ʱ��3�жϺ���
{
	static u8 i=0;
	if(TIM_GetITStatus(TIM3,TIM_IT_Update)==SET)  //������������ж�
	{
    i++;
		if(i >= 10)                                 //ÿ��60S����һ��������
		{
			i=0;
			lenght=mqtt_ping_message(package);
			Usart3_SendBuf(package,lenght);
			nms=30;
			while((rxbuf[0]!=ping[0] && rxbuf[1]!=ping[1]) && nms--)
			{
				 delay_ms(100);
			}
			printf("\r\nSend ping package is successful!\r\n");
		}
	}
	TIM_ClearITPendingBit(TIM3,TIM_IT_Update);  //�����ʱ���ж�3������λ
}

