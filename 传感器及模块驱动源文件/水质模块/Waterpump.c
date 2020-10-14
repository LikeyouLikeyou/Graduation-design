#include "Waterpump.h"


/*
  *****************************************************************************
  * @Name   : GPIO��ʼ������,ˮ�ü̵���IO��ʼ��
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
void GPIO_Initialization(void)
{
    GPIO_InitTypeDef GPIO_InitStruction;                         //�ṹ������
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);         //ʹ��APB2����ʱ��

    GPIO_InitStruction.GPIO_Mode=GPIO_Mode_Out_PP;               //�������
    GPIO_InitStruction.GPIO_Pin=GPIO_Pin_5|GPIO_Pin_6;           //PB5����עˮ   PB6������ˮ
    GPIO_InitStruction.GPIO_Speed=GPIO_Speed_50MHz;              //�˿�����Ϊ50MHz
    GPIO_Init(GPIOB,&GPIO_InitStruction);                        //��ʼ��GPIO
	  GPIO_ResetBits(GPIOB,GPIO_Pin_5|GPIO_Pin_6);                 //Ĭ������͵�ƽ
}


