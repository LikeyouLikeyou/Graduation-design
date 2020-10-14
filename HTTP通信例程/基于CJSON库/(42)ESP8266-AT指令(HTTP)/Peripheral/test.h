#ifndef  __TEST_H
#define	 __TEST_H


#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "stm32f10x.h"
#include "esp8266.h"
#include "delay.h"
#include "keypros.h"
#include "http.h"



/********************************** �û���Ҫ���õĲ���**********************************/
#define      macUser_ESP8266_ApSsid                       "Tenda_A22AC0"               //Ҫ���ӵ��ȵ������
#define      macUser_ESP8266_ApPwd                        "limutong@qq.com"            //Ҫ���ӵ��ȵ������


//HTTP������IP���˿ں�
#define      macUser_ESP8266_TcpServer_IP                 "47.115.119.0"               //Ҫ���ӵķ������� IP
#define      macUser_ESP8266_TcpServer_Port               "3001"                       //Ҫ���ӵķ������Ķ˿�





/********************************** �ⲿȫ�ֱ��� ***************************************/
extern volatile uint8_t ucTcpClosedFlag;



/********************************** ���Ժ������� ***************************************/
void  ESP8266_Configuration(void);                               //͸��ǰESP8266����
void  Reconnection(void);                                        //������������
void  ESP8266_StaTcpClient_UnvarnishTest  ( void );              //͸��ʵ��



#endif

