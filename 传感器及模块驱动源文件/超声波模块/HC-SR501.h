#ifndef __HR_SR501_H_
#define __HR_SR501_H_

#include "stm32f10x.h"

#define HCSR501 GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_1)    //��ȡ��������ֵ���ߵ�ƽ���ʾ���˽����������

void HCSR501_Initialization(void);

#endif
