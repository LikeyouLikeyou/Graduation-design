#include "heartbeat.h"

__IO uint8_t flag=0;
/*
  *****************************************************************************
  * @Name   : void Timer_init(u16 arr,u16 psc)
  *
  * @Brief  : Tout(溢出时间)=(ARR+1)(PSC+1)/Tclk
	*           Tclk：定时器的输入时钟频率（单位MHZ）也就是CK_INT时钟
	*           Tout：定时器溢出时间（单位为s）
  *           (psc+1))/Tclk*1是计算的计数器减少一个数所用的时间(单位为s)
	*           那么(psc+1))/Tclk*5000就是一次定时器的时间
	*
  * @Input  : arr：下一个更新事件装入活动的自动重装载寄存器周期的值
  *           psc：用来作为TIMx时钟频率除数的预分频值 
  *           	
  * @Output : none
  *
  * @Return : none
  *****************************************************************************
 */
void Timer_init(u16 arr,u16 psc)                                //定时器初始化函数   之所以这里是u16类型是因为此处的寄存器是16位的
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitstruct;
	NVIC_InitTypeDef NVIC_InitStruct;
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);           //使能内部时钟(CK_INT)

	/* 定时器初始化配置 */
	TIM_TimeBaseInitstruct.TIM_Period=arr;                        //设置在下一个更新事件装入活动的自动重装载寄存器周期的值
	TIM_TimeBaseInitstruct.TIM_Prescaler=psc;                     //设置用来作为TIMx时钟频率除数的预分频值
  TIM_TimeBaseInitstruct.TIM_ClockDivision=TIM_CKD_DIV1;        //设置时钟分割:TDTS=Tck_tim
	TIM_TimeBaseInitstruct.TIM_CounterMode=TIM_CounterMode_Up;    //向上计数模式
	TIM_TimeBaseInit(TIM3,&TIM_TimeBaseInitstruct);              //初始化时间基数单位 ·
	
	TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE);                     //使能定时器3更新中断
	
	TIM_Cmd(TIM3,ENABLE);                                       //使能定时器3
	
	
	/* Configure the NVIC Preemption Priority Bits */  
	NVIC_PriorityGroupConfig ( NVIC_PriorityGroup_2 );
	
	/*中断优先级设置*/
	NVIC_InitStruct.NVIC_IRQChannel=TIM3_IRQn;                  //定时器3全局中断通道
	NVIC_InitStruct.NVIC_IRQChannelCmd=ENABLE;                  //使能IRQ通道
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority=0;        //抢占优先级
	NVIC_InitStruct.NVIC_IRQChannelSubPriority=3;               //响应优先级
  NVIC_Init(&NVIC_InitStruct);
}

void TIM3_IRQHandler()  //定时器3中断函数,5S中断一次
{
	static uint8_t num=0;
	if(TIM_GetITStatus(TIM3,TIM_IT_Update)==SET)  //如果发生更新中断
	{
		num++;
		if(num>=10)
		{
			num=0;
			flag=1;
		}
		TIM_ClearITPendingBit(TIM3,TIM_IT_Update);  //清楚定时器中断3待处理位
	}
}

