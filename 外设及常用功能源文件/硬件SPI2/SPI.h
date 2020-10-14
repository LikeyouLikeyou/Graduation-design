#ifndef _SPI_H_
#define _SPI_H_


#include "stm32f10x.h"
#include "delay.h"

void SPI_Configuration(void);                   //硬件SPI2初始化函数
u8 SPI2_Write_Read_Byte(uint8_t TX_Data);       //硬件SPI2发送与接收函数

#endif
