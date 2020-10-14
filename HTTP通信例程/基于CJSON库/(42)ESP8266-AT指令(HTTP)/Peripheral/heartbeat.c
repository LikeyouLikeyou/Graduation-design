#include "heartbeat.h"

__IO uint8_t flag=0;
/*
  *****************************************************************************
  * @Name   : void Timer_init(u16 arr,u16 psc)
  *
  * @Brief  : Tout(���ʱ��)=(ARR+1)(PSC+1)/Tclk
	*           Tclk����ʱ��������ʱ��Ƶ�ʣ���λMHZ��Ҳ����CK_INTʱ��
	*           Tout����ʱ�����ʱ�䣨��λΪs��
  *           (psc+1))/Tclk*1�Ǽ���ļ���������һ�������õ�ʱ��(��λΪs)
	*           ��ô(psc+1))/Tclk*5000����һ�ζ�ʱ����ʱ��
	*
  * @Input  : arr����һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ
  *           psc��������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ 
  *           	
  * @Output : none
  *
  * @Return : none
  *****************************************************************************
 */
void Timer_init(u16 arr,u16 psc)                                //��ʱ����ʼ������   ֮����������u16��������Ϊ�˴��ļĴ�����16λ��
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitstruct;
	NVIC_InitTypeDef NVIC_InitStruct;
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);           //ʹ���ڲ�ʱ��(CK_INT)

	/* ��ʱ����ʼ������ */
	TIM_TimeBaseInitstruct.TIM_Period=arr;                        //��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ
	TIM_TimeBaseInitstruct.TIM_Prescaler=psc;                     //����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ
  TIM_TimeBaseInitstruct.TIM_ClockDivision=TIM_CKD_DIV1;        //����ʱ�ӷָ�:TDTS=Tck_tim
	TIM_TimeBaseInitstruct.TIM_CounterMode=TIM_CounterMode_Up;    //���ϼ���ģʽ
	TIM_TimeBaseInit(TIM3,&TIM_TimeBaseInitstruct);              //��ʼ��ʱ�������λ ��
	
	TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE);                     //ʹ�ܶ�ʱ��3�����ж�
	
	TIM_Cmd(TIM3,ENABLE);                                       //ʹ�ܶ�ʱ��3
	
	
	/* Configure the NVIC Preemption Priority Bits */  
	NVIC_PriorityGroupConfig ( NVIC_PriorityGroup_2 );
	
	/*�ж����ȼ�����*/
	NVIC_InitStruct.NVIC_IRQChannel=TIM3_IRQn;                  //��ʱ��3ȫ���ж�ͨ��
	NVIC_InitStruct.NVIC_IRQChannelCmd=ENABLE;                  //ʹ��IRQͨ��
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority=0;        //��ռ���ȼ�
	NVIC_InitStruct.NVIC_IRQChannelSubPriority=3;               //��Ӧ���ȼ�
  NVIC_Init(&NVIC_InitStruct);
}

void TIM3_IRQHandler()  //��ʱ��3�жϺ���,5S�ж�һ��
{
	static uint8_t num=0;
	if(TIM_GetITStatus(TIM3,TIM_IT_Update)==SET)  //������������ж�
	{
		num++;
		if(num>=10)
		{
			num=0;
			flag=1;
		}
		TIM_ClearITPendingBit(TIM3,TIM_IT_Update);  //�����ʱ���ж�3������λ
	}
}

