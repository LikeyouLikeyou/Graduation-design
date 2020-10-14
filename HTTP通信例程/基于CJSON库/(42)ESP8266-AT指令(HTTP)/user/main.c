/**
  ******************************************************************************
  * @file    main.c
  * @date    28-2-2020
  * @brief   主要实现ESP8266TCP透传
  ******************************************************************************
  * @attention
  *
  *
  *
  *
  ******************************************************************************
  */

#include "usart1.h"
#include "esp8266.h"
#include "BitOperation.h"
#include "test.h"
#include "delay.h"
#include "keypros.h"


int main()
{	
	 key_pros_Init();
	 USARTx_Config();
	 ESP8266_Init ();
	
	 printf ( "\r\nESP8266测试\r\n" ); 
   ESP8266_StaTcpClient_UnvarnishTest();
	
	 while(1);
}




