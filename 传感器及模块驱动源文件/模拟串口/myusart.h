#ifndef __MYUSART_H_
#define __MYUSART_H_

#include "stm32f10x.h"
#include "BitOperation.h"


enum{
	COM_START_BIT,          //起始位
	COM_D0_BIT,             //数据位，在传输过程中是低位在前高位在后
	COM_D1_BIT,
	COM_D2_BIT,
	COM_D3_BIT,
	COM_D4_BIT,
	COM_D5_BIT,
	COM_D6_BIT,
	COM_D7_BIT,
	COM_STOP_BIT,          //停止位
};

#define IO_TXD PBout(0)
#define IO_RXD PBin(1)

#define BuadRate_9600 104

extern u8 len,USART_BUFF[11];

void GPIO_Initialization(void);
void Timer_init(u16 arr,u16 psc);

void USART_Send(u8 *buff,u8 len);        //发送函数

#endif
