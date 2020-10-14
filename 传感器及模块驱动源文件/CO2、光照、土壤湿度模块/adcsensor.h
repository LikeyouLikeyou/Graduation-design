#ifndef __ADCSENSOR_H
#define __ADCSENSOR_H	

#include "stm32f10x.h"


void Adc_Init(void);                    //ADC��ʼ��

float CO2_Concentration(void);           //CO2Ũ��
float Soil_moisture(void);               //����ʪ��
float Light_intensity(void);             //����ǿ��

#endif 
