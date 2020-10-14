#include "pwm.h"
#include "delay.h"


/*
  *****************************************************************************
  * @Name   : GPIO初始化函数
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
	  GPIO_PinRemapConfig(GPIO_PartialRemap_TIM3,ENABLE);                            //部分重映射
	
    GPIO_InitStruction.GPIO_Mode=GPIO_Mode_AF_PP;
    GPIO_InitStruction.GPIO_Pin=GPIO_Pin_5;
    GPIO_InitStruction.GPIO_Speed=GPIO_Speed_50MHz;

    GPIO_Init(GPIOB,&GPIO_InitStruction);
}


//Tout = （（arr+1）*（psc+1））/Tclk ;
//Tclk：定时器的输入时钟频率（单位MHZ）也就是CK_INT时钟此处为72MHz
//Tout：定时器溢出时间（单位为s）

/**************************************************************
函数名称: TIM4_Init(u16 arr,u16 psc)
函数功能: 定时4初始化，TIM4_CH4
输入参数: 
         arr：自动重装值
         psc：时钟预分频数
			
返 回 值: 无
备    注: 无
**************************************************************/
void TIM3_Init(u16 arr,u16 psc)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);          //使能TIM4的时钟
	
	TIM_TimeBaseInitStruct.TIM_Period=arr;                       //设置重装载值
	TIM_TimeBaseInitStruct.TIM_Prescaler=psc;                    //设置预分频值
	TIM_TimeBaseInitStruct.TIM_ClockDivision=0;                  //TIM_ClockDivision是改变做输入捕获时滤波用的并不是定时器的分频器
	TIM_TimeBaseInitStruct.TIM_CounterMode=TIM_CounterMode_Up;   //向上计数
	TIM_TimeBaseInitStruct.TIM_RepetitionCounter=0;              //默认配置为0
	
	TIM_TimeBaseInit(TIM3,&TIM_TimeBaseInitStruct);
	TIM_Cmd(TIM3,ENABLE);                                        //使能TIM2时钟
}

void PWM_Init()
{
	TIM_OCInitTypeDef TIM_OCInitStruct;
	
	TIM_OCInitStruct.TIM_OCMode=TIM_OCMode_PWM2;              //脉宽调制模式2,TIM3_CNT>TIM3_CCR2时通道2为有效电平
	TIM_OCInitStruct.TIM_OutputState=TIM_OutputState_Enable;  //比较输出使能
	TIM_OCInitStruct.TIM_OCPolarity=TIM_OCPolarity_Low;      //TIM输出比较极性高
	TIM_OC2Init(TIM3,&TIM_OCInitStruct);                      //通道2初始化函数

	TIM_OC2PreloadConfig(TIM3,TIM_OCPreload_Enable);          //使能TIM3在CCR2上的预装载寄存器
	TIM_ARRPreloadConfig(TIM3,ENABLE);                        //使能TIM3在ARR上的预装载寄存器
}

void PWM_Output(u16 Compare2)
{
	TIM_SetCompare2(TIM3,Compare2);                            //不断改变比较值CCRx，达到不同的占空比效果
}


