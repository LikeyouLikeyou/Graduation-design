#include "Waterpump.h"


/*
  *****************************************************************************
  * @Name   : GPIO初始化函数,水泵继电器IO初始化
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
    GPIO_InitTypeDef GPIO_InitStruction;                         //结构体声明
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);         //使能APB2外设时钟

    GPIO_InitStruction.GPIO_Mode=GPIO_Mode_Out_PP;               //推挽输出
    GPIO_InitStruction.GPIO_Pin=GPIO_Pin_5|GPIO_Pin_6;           //PB5——注水   PB6——排水
    GPIO_InitStruction.GPIO_Speed=GPIO_Speed_50MHz;              //端口速率为50MHz
    GPIO_Init(GPIOB,&GPIO_InitStruction);                        //初始化GPIO
	  GPIO_ResetBits(GPIOB,GPIO_Pin_5|GPIO_Pin_6);                 //默认输出低电平
}


