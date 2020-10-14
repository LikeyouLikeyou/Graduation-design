#ifndef __USART2_H
#define __USART2_H

#include "stm32f10x.h"
#include "ESP01.h"

extern u8 txbuf[256];
extern u8 rxbuf[256];

void Usart2_Configuration(u32 BAUD);
void Usart2_SendByte(u8 val);
void Usart2_SendBuf(u8 *buf,u8 len);
void Usart2_SendString(char *str);

#endif



/*********************************************END OF FILE********************************************/

