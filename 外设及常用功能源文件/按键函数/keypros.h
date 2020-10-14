#ifndef _keypros_h
#define _keypros_h

#include "stm32f10x.h"
#include "delay.h"

#define key_wk_up GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0)  //��ȡ����wk_up��ֵ
#define key_0 GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_4)      //��ȡ����0��ֵ
#define key_1 GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_3)      //��ȡ����1��ֵ
#define key_2 GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_2)      //��ȡ����2��ֵ

#define key_wk_up_press  1  //����wk_up����
#define key_0_press      2  //����0����
#define key_1_press      3  //����1����
#define key_2_press      4  //����2����

void key_pros_Init(void);
u8 key_scan(u8 mode);           //mode��Ϊ0��1   0��������  1������


#endif


/*ʹ��ʾ��
*
*  while(1)
*  {
*	    KEY=key_scan(0);   //������ģʽ,���ҿ�ʼɨ�谴��(������������˼����������û���ɿ�ֻ����һ��.����������˼����������û�ɿ�����)
*	    if(KEY)   //����а�������
*	    {
*		     switch(KEY)
*		     {
*			     case 1:GPIO_SetBits(GPIOB,GPIO_Pin_8); break;            //����wk_up����,�÷�����Ϊ�ߵ�ƽ(��)
*			     case 2:GPIO_Write(GPIOB,0);GPIO_Write(GPIOE,0);break;    //����0����,����һ����
*			     case 3:GPIO_WriteBit(GPIOB,GPIO_Pin_5,Bit_RESET); break; //����1����,�����
*			     case 4:GPIOE->ODR&=~(1<<5); break;                       //����2����,�̵���
*		     }
*		    delay_ms(10);
*	    }
*   }
*/