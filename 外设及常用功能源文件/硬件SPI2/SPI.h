#ifndef _SPI_H_
#define _SPI_H_


#include "stm32f10x.h"
#include "delay.h"

void SPI_Configuration(void);                   //Ӳ��SPI2��ʼ������
u8 SPI2_Write_Read_Byte(uint8_t TX_Data);       //Ӳ��SPI2��������պ���

#endif
