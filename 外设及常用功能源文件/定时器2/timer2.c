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

/* ID������ */
char strdata[5]={0};

/* ���ͻ����� */
char sendDat[256]={0};


/* ����ת�ַ����� */
char * myitoa(int value, char * str)
{
        char * pstr = str; //str�����ܸı䣬һ��Ҫ����str
	      int wei = 1;  //������һλ
        int ivalue = value; //���ڲ��Գ���
	
        if (value < 0)
        {
                *pstr = '-';
                pstr++;
                value *= -1; //ת��Ϊ��������
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
��������: Timer_init(u16 arr,u16 psc)
��������: ��ʼ����ʱ��
�������:
          arr���Զ���װֵ��
          psc��ʱ��Ԥ��Ƶ��

˵����
     Tout(���ʱ��)=(ARR+1)(PSC+1)/Tclk
		 Tclk����ʱ��������ʱ��Ƶ�ʣ���λMHZ��Ҳ����CK_INTʱ��
		 Tout����ʱ�����ʱ�䣨��λΪs��
		 (psc+1))/Tclk*1�Ǽ���ļ���������һ�������õ�ʱ��(��λΪs)
		 ��ô(psc+1))/Tclk*5000����һ�ζ�ʱ����ʱ��

�� �� ֵ: ��
��    ע: ��
**************************************************************/
void Timer2_init(u16 arr,u16 psc)                                      //��ʱ����ʼ������   ֮����������u16��������Ϊ�˴��ļĴ�����16λ��
{
    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitstruct;
    NVIC_InitTypeDef NVIC_InitStruct;
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);                 //ʹ���ڲ�ʱ��(CK_INT)
    /* ��ʱ������ */
    TIM_TimeBaseInitstruct.TIM_Period=arr;                              //��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ
    TIM_TimeBaseInitstruct.TIM_Prescaler=psc;                           //����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ
    TIM_TimeBaseInitstruct.TIM_ClockDivision=TIM_CKD_DIV1;              //����ʱ�ӷָ�:TDTS=Tck_tim
    TIM_TimeBaseInitstruct.TIM_CounterMode=TIM_CounterMode_Up;          //���ϼ���ģʽ

    TIM_TimeBaseInit(TIM2,&TIM_TimeBaseInitstruct);                     //��ʼ��ʱ�������λ ��

    TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE);                            //ʹ�ܶ�ʱ��3�����ж�

    /*�ж����ȼ�����*/
    NVIC_InitStruct.NVIC_IRQChannel=TIM2_IRQn;                          //��ʱ��3ȫ���ж�ͨ��
    NVIC_InitStruct.NVIC_IRQChannelCmd=ENABLE;                          //ʹ��IRQͨ��
    NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority=0;                //��ռ���ȼ�
    NVIC_InitStruct.NVIC_IRQChannelSubPriority=0;                       //��Ӧ���ȼ�
    NVIC_Init(&NVIC_InitStruct);

    TIM_Cmd(TIM2,ENABLE);                                               //ʹ�ܶ�ʱ��3
}


//Ҫȡ��[a,b)�����������ʹ��(rand() % (b-a))+ a �����ֵ��a����b����
//Ҫȡ��[a,b]�����������ʹ��(rand() % (b-a+1))+ a �����ֵ��a��b����
//Ҫȡ��(a,b]�����������ʹ��(rand() % (b-a))+ a + 1 �����ֵ����a��b����


void TIM2_IRQHandler()                          //��ʱ��3�жϺ���
{
    if(TIM_GetITStatus(TIM2,TIM_IT_Update)==SET)  //������������ж�
    {

//				sprintf(sendDat,"{\"method\":\"thing.service.property.set\",\"id\":\"%s\",\"params\":{\"Temperature\":%d,\"Humidity\":%d,\"mq\":%02.1f,\"Buzzer\":%d},\"version\":\"1.0.0\"}",myitoa(((rand() % 9999)+ 10002),strdata),temperature,humidity,Get_MQ_2(),flag);
//				if(!MQTT_Publish("/sys/a17qlYzKRRM/car1/thing/event/property/post",sendDat))                                       //������Ϣ
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
//        /* ����GPS��Ϣ */
//        if(!MQTT_Publish("/sys/a17qlYzKRRM/car1/thing/event/property/post",sendDat))                                       //������Ϣ
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
    TIM_ClearITPendingBit(TIM2,TIM_IT_Update);  //�����ʱ���ж�3������λ
}

