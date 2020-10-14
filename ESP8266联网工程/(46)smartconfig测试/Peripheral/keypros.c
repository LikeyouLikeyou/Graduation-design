#include "keypros.h"

void key_pros_Init()  //按键初始化函数
{
	GPIO_InitTypeDef GPIO_InitStruct;
	SystemInit();
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOE,ENABLE);
	
	/* 绿灯 */
	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_IPD; //配置为下拉输入
	GPIO_InitStruct.GPIO_Pin=GPIO_Pin_0;
	GPIO_InitStruct.GPIO_Speed= GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStruct);
	
	/* 红灯 */
	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_IPU;  //配置为上拉输入
	GPIO_InitStruct.GPIO_Pin=GPIO_Pin_4|GPIO_Pin_3|GPIO_Pin_2;
	GPIO_InitStruct.GPIO_Speed= GPIO_Speed_50MHz;
	GPIO_Init(GPIOE,&GPIO_InitStruct);
}

u8 key_scan(u8 mode)
{
	static u8 key=1;  //只会执行一次
	if(mode==1)   //判断是否支持连按,mode=1则支持连按
		key =1;
	if(key&&(key_0==0||key_1==0||key_2==0||key_wk_up==1))  //如果四个按键有一个按下
	{
		delay_ms(10);
		key=0;
		if(key_0==0)   //如果按键0按下
		{
			return key_0_press;  //则返回其键值2
		}
		else if(key_1==0)  //如果按键1按下
		{
			return key_1_press;  //则返回其键值3
		}
		else if(key_2==0)  //如果按键2按下
		{
			return key_2_press;  //则返回其键值4
		}
		else if(key_wk_up==1)  //如果按键wk_up按下
		{
			return key_wk_up_press;   //则返回其键值1
		}
	 }else if(key_0==1&&key_1==1&&key_2==1&&key_wk_up==0)   //否则如果没有按键按下
	  { 
		  key=1;
	  }
	  return 0; //如果key=0(也就还支持连按)时第一个if为假,没有按键按下时第二个if也为假此时返回0,不进行任何操作
}
