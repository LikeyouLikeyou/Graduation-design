#include "timer2.h"
#include "usart2.h"
#include "mymqtt.h"
#include "printf.h"
#include "delay.h"
#include <stdlib.h>
#include <string.h>
#include "DHT11.h"
#include "MQ-2.h"
#include "main.h"

/* ID缓存区 */
char strdata[5]={0};

/* 发送缓存区 */
char sendDat[256]={0};


/* 整形转字符类型 */
char * myitoa(int value, char * str)
{
        char * pstr = str; //str本身不能改变，一会要返回str
	      int wei = 1;  //数至少一位
        int ivalue = value; //用于测试长度
	
        if (value < 0)
        {
                *pstr = '-';
                pstr++;
                value *= -1; //转变为正数处理
        }

        while ((ivalue /=   10) != 0)
        {
                wei++;
        }
 
        pstr += wei-1;
        while (value % 10 != 0)
        {
                *pstr-- = (value % 10)+'0';
                value /= 10;
        }
        return str;
}





/**************************************************************
函数名称: Timer_init(u16 arr,u16 psc)
函数功能: 初始化定时器
输入参数:
          arr：自动重装值。
          psc：时钟预分频数

说明：
     Tout(溢出时间)=(ARR+1)(PSC+1)/Tclk
		 Tclk：定时器的输入时钟频率（单位MHZ）也就是CK_INT时钟
		 Tout：定时器溢出时间（单位为s）
		 (psc+1))/Tclk*1是计算的计数器减少一个数所用的时间(单位为s)
		 那么(psc+1))/Tclk*5000就是一次定时器的时间

返 回 值: 无
备    注: 无
**************************************************************/
void Timer2_init(u16 arr,u16 psc)                                      //定时器初始化函数   之所以这里是u16类型是因为此处的寄存器是16位的
{
    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitstruct;
    NVIC_InitTypeDef NVIC_InitStruct;
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);                 //使能内部时钟(CK_INT)
    /* 定时器设置 */
    TIM_TimeBaseInitstruct.TIM_Period=arr;                              //设置在下一个更新事件装入活动的自动重装载寄存器周期的值
    TIM_TimeBaseInitstruct.TIM_Prescaler=psc;                           //设置用来作为TIMx时钟频率除数的预分频值
    TIM_TimeBaseInitstruct.TIM_ClockDivision=TIM_CKD_DIV1;              //设置时钟分割:TDTS=Tck_tim
    TIM_TimeBaseInitstruct.TIM_CounterMode=TIM_CounterMode_Up;          //向上计数模式

    TIM_TimeBaseInit(TIM2,&TIM_TimeBaseInitstruct);                     //初始化时间基数单位 ·

    TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE);                            //使能定时器3更新中断

    /*中断优先级设置*/
    NVIC_InitStruct.NVIC_IRQChannel=TIM2_IRQn;                          //定时器3全局中断通道
    NVIC_InitStruct.NVIC_IRQChannelCmd=ENABLE;                          //使能IRQ通道
    NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority=0;                //抢占优先级
    NVIC_InitStruct.NVIC_IRQChannelSubPriority=0;                       //响应优先级
    NVIC_Init(&NVIC_InitStruct);

    TIM_Cmd(TIM2,ENABLE);                                               //使能定时器3
}


//要取得[a,b)的随机整数，使用(rand() % (b-a))+ a （结果值含a不含b）。
//要取得[a,b]的随机整数，使用(rand() % (b-a+1))+ a （结果值含a和b）。
//要取得(a,b]的随机整数，使用(rand() % (b-a))+ a + 1 （结果值不含a含b）。


void TIM2_IRQHandler()                          //定时器3中断函数
{
    if(TIM_GetITStatus(TIM2,TIM_IT_Update)==SET)  //如果发生更新中断
    {

//				sprintf(sendDat,"{\"method\":\"thing.service.property.set\",\"id\":\"%s\",\"params\":{\"Temperature\":%d,\"Humidity\":%d,\"mq\":%02.1f,\"Buzzer\":%d},\"version\":\"1.0.0\"}",myitoa(((rand() % 9999)+ 10002),strdata),temperature,humidity,Get_MQ_2(),flag);
//				if(!MQTT_Publish("/sys/a17qlYzKRRM/car1/thing/event/property/post",sendDat))                                       //发布消息
//				{
//					printf("MQTT Pub is OK!\r\n");
//					memset(sendDat,0,256);
//					memset(strdata,0,5);
//				}
//				else
//				{
//					printf("MQTT PubGPS is Error!\r\n");
//					memset(strdata,0,5);
//					memset(sendDat,0,256);
//				}
//				

//				sprintf(sendDat,"{\"method\":\"thing.service.property.set\",\"id\":\"%s\",\"params\":{\"GeoLocation\":{\"Latitude\":115.3541305,\"Longitude\":36.3913452}},\"version\":\"1.0.0\"}",myitoa(((rand()%9999)+2),strdata));
//				
//        /* 发布GPS信息 */
//        if(!MQTT_Publish("/sys/a17qlYzKRRM/car1/thing/event/property/post",sendDat))                                       //发布消息
//        {
//            printf("MQTT PubGPS is OK!\r\n");
//						memset(strdata,0,5);
//					  memset(sendDat,0,256);
//        }
//        else
//        {
//            printf("MQTT PubGPS is Error!\r\n");
//						memset(strdata,0,5);
//					  memset(sendDat,0,256);
//        }
				
    }
    TIM_ClearITPendingBit(TIM2,TIM_IT_Update);  //清楚定时器中断3待处理位
}

