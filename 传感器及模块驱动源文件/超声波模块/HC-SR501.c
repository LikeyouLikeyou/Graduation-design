#include "HC-SR501.h"

/*
  *****************************************************************************
  * @Name   : GPIO��ʼ������
  *
  * @Brief  : ��ʼ��PA1�������������������
  *
  * @Input  : none
  *
  * @Output : none
  *
  * @Return : none
  *****************************************************************************
 */
void HCSR501_Initialization(void)
{
    GPIO_InitTypeDef GPIO_InitStruction;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);

    GPIO_InitStruction.GPIO_Mode=GPIO_Mode_IPU;         //��������
    GPIO_InitStruction.GPIO_Pin=GPIO_Pin_1;
    GPIO_InitStruction.GPIO_Speed=GPIO_Speed_50MHz;

    GPIO_Init(GPIOA,&GPIO_InitStruction);
}
