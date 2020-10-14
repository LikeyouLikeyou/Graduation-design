#include "pwm.h"
#include "delay.h"


/*
  *****************************************************************************
  * @Name   : GPIO��ʼ������
  *
  * @Brief  : none
  *
  * @Input  : none
  *
  * @Output : none
  *
  * @Return : none
  *****************************************************************************
 */
void PWM_Initialization()
{
    GPIO_InitTypeDef GPIO_InitStruction;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB|RCC_APB2Periph_AFIO,ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);
	  GPIO_PinRemapConfig(GPIO_PartialRemap_TIM3,ENABLE);                            //������ӳ��
	
    GPIO_InitStruction.GPIO_Mode=GPIO_Mode_AF_PP;
    GPIO_InitStruction.GPIO_Pin=GPIO_Pin_5;
    GPIO_InitStruction.GPIO_Speed=GPIO_Speed_50MHz;

    GPIO_Init(GPIOB,&GPIO_InitStruction);
}


//Tout = ����arr+1��*��psc+1����/Tclk ;
//Tclk����ʱ��������ʱ��Ƶ�ʣ���λMHZ��Ҳ����CK_INTʱ�Ӵ˴�Ϊ72MHz
//Tout����ʱ�����ʱ�䣨��λΪs��

/**************************************************************
��������: TIM4_Init(u16 arr,u16 psc)
��������: ��ʱ4��ʼ����TIM4_CH4
�������: 
         arr���Զ���װֵ
         psc��ʱ��Ԥ��Ƶ��
			
�� �� ֵ: ��
��    ע: ��
**************************************************************/
void TIM3_Init(u16 arr,u16 psc)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);          //ʹ��TIM4��ʱ��
	
	TIM_TimeBaseInitStruct.TIM_Period=arr;                       //������װ��ֵ
	TIM_TimeBaseInitStruct.TIM_Prescaler=psc;                    //����Ԥ��Ƶֵ
	TIM_TimeBaseInitStruct.TIM_ClockDivision=0;                  //TIM_ClockDivision�Ǹı������벶��ʱ�˲��õĲ����Ƕ�ʱ���ķ�Ƶ��
	TIM_TimeBaseInitStruct.TIM_CounterMode=TIM_CounterMode_Up;   //���ϼ���
	TIM_TimeBaseInitStruct.TIM_RepetitionCounter=0;              //Ĭ������Ϊ0
	
	TIM_TimeBaseInit(TIM3,&TIM_TimeBaseInitStruct);
	TIM_Cmd(TIM3,ENABLE);                                        //ʹ��TIM2ʱ��
}

void PWM_Init()
{
	TIM_OCInitTypeDef TIM_OCInitStruct;
	
	TIM_OCInitStruct.TIM_OCMode=TIM_OCMode_PWM2;              //�������ģʽ2,TIM3_CNT>TIM3_CCR2ʱͨ��2Ϊ��Ч��ƽ
	TIM_OCInitStruct.TIM_OutputState=TIM_OutputState_Enable;  //�Ƚ����ʹ��
	TIM_OCInitStruct.TIM_OCPolarity=TIM_OCPolarity_Low;      //TIM����Ƚϼ��Ը�
	TIM_OC2Init(TIM3,&TIM_OCInitStruct);                      //ͨ��2��ʼ������

	TIM_OC2PreloadConfig(TIM3,TIM_OCPreload_Enable);          //ʹ��TIM3��CCR2�ϵ�Ԥװ�ؼĴ���
	TIM_ARRPreloadConfig(TIM3,ENABLE);                        //ʹ��TIM3��ARR�ϵ�Ԥװ�ؼĴ���
}

void PWM_Output(u16 Compare2)
{
	TIM_SetCompare2(TIM3,Compare2);                            //���ϸı�Ƚ�ֵCCRx���ﵽ��ͬ��ռ�ձ�Ч��
}


