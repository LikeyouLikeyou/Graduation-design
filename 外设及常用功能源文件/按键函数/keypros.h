#ifndef _keypros_h
#define _keypros_h

#include "stm32f10x.h"
#include "delay.h"

#define key_wk_up GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0)  //读取按键wk_up的值
#define key_0 GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_4)      //读取按键0的值
#define key_1 GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_3)      //读取按键1的值
#define key_2 GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_2)      //读取按键2的值

#define key_wk_up_press  1  //按键wk_up按下
#define key_0_press      2  //按键0按下
#define key_1_press      3  //按键1按下
#define key_2_press      4  //按键2按下

void key_pros_Init(void);
u8 key_scan(u8 mode);           //mode分为0和1   0：不连按  1：连按


#endif


/*使用示例
*
*  while(1)
*  {
*	    KEY=key_scan(0);   //不连按模式,并且开始扫描按键(不连续按的意思：按键按下没有松开只能算一次.连续按的意思：按键按下没松开算多次)
*	    if(KEY)   //如果有按键按下
*	    {
*		     switch(KEY)
*		     {
*			     case 1:GPIO_SetBits(GPIOB,GPIO_Pin_8); break;            //按键wk_up按下,让蜂鸣器为高电平(响)
*			     case 2:GPIO_Write(GPIOB,0);GPIO_Write(GPIOE,0);break;    //按键0按下,红绿一起亮
*			     case 3:GPIO_WriteBit(GPIOB,GPIO_Pin_5,Bit_RESET); break; //按键1按下,红灯亮
*			     case 4:GPIOE->ODR&=~(1<<5); break;                       //按键2按下,绿灯亮
*		     }
*		    delay_ms(10);
*	    }
*   }
*/