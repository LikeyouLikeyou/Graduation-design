#ifndef __HEARTBEAT_H_
#define __HEARTBEAT_H_

#include "stm32f10x.h"

extern __IO uint8_t flag;         //ÉùÃ÷±äÁ¿

void Timer_init(u16 arr,u16 psc);


#endif
