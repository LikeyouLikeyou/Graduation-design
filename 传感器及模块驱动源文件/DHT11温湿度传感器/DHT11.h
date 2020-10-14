#ifndef __DHT11_H_
#define __DHT11_H_

#include "stm32f10x.h"
#include "BitOperation.h"      //λ������
#include "delay.h"

//IO��������
#define DHT11_IO_IN()  {GPIOB->CRH&=0XFFFFFF0F;GPIOB->CRH|=8<<4;}
#define DHT11_IO_OUT() {GPIOB->CRH&=0XFFFFFF0F;GPIOB->CRH|=3<<4;}
////IO��������
#define	DHT11_DQ_OUT PBout(9) //���ݶ˿�	PB9
#define	DHT11_DQ_IN  PBin(9)  //���ݶ˿�	PB9 


u8 DHT11_Init(void);                     //��ʼ��DHT11
u8 DHT11_Read_Data(u8 *temp,u8 *humi);   //��ȡ��ʪ��
u8 DHT11_Check(void);                    //����Ƿ����DHT11
void DHT11_Rst(void);                    //��λDHT11

#endif
