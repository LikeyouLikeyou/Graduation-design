#ifndef __USART1_H
#define __USART1_H

#include "stm32f10x.h"
#include <stdio.h>

void Usart1_Configuration(u32 BAUD);
void Usart1_SendByte(u8 val);
void Usart1_SendBuf(u8 *buf,u8 len);
void Usart1_SendString(char *str);

#endif



/*********************************************END OF FILE********************************************/

