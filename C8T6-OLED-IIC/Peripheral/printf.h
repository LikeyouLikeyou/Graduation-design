#ifndef _PRINTF_H_
#define _PRINTF_H_

#include "stm32f10x.h"
#include "stdio.h"

#define RECEIVE_INTERRUPT 0    //是否开启串口1接收中断，如果要使用scanf就无需开启反之则要开启   0：不开启   1：开启 

void USART_Initialization(u32 Baud);

#endif

