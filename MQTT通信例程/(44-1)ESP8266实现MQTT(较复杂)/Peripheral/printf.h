#ifndef _PRINTF_H_
#define _PRINTF_H_

#include "stm32f10x.h"
#include "stdio.h"

#define RECEIVE_INTERRUPT 0    //�Ƿ�������1�����жϣ����Ҫʹ��scanf�����迪����֮��Ҫ����   0��������   1������ 

void USART_Initialization(u32 Baud);

#endif

