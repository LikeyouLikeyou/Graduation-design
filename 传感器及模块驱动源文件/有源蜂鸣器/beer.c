#include "beer.h"
#include "delay.h"

/*
  *****************************************************************************
  * @Name   : ·äÃùÆ÷GPIO³õÊ¼»¯º¯Êý
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
void Beer_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStruction;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);

    GPIO_InitStruction.GPIO_Mode=GPIO_Mode_Out_PP;
    GPIO_InitStruction.GPIO_Pin=GPIO_Pin_6;
    GPIO_InitStruction.GPIO_Speed=GPIO_Speed_50MHz;
    GPIO_Init(GPIOA,&GPIO_InitStruction);
	  GPIO_ResetBits(GPIOA,GPIO_Pin_6);
}



