#ifndef __USART3_H
#define __USART3_H

#include "stm32f10x.h"

extern u8 txbuf[256];
extern char rxbuf[256];

extern u8 UsartReadFlage;

void Usart3_Configuration(u32 BAUD);
void Usart3_SendByte(u8 val);
void Usart3_SendBuf(u8 *buf,u8 len);
void Usart3_SendString(char *str);

#endif



/*********************************************END OF FILE********************************************/

