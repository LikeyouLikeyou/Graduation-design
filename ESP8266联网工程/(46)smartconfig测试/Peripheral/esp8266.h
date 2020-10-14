#ifndef __ESP8266_H_
#define __ESP8266_H_

#include <stdio.h>
#include <string.h>

#include "stm32f10x.h"
#include "usart1.h"
#include "usart3.h"
#include "delay.h"
#include "led.h"


#define SSID         "Tenda_A22AC0"                //�ȵ�����
#define PWD          "limutong@qq.com"             //�ȵ�����

#define TCP          "TCP"                         //Э��
#define SERVER_IP    "106.54.47.12"                //������IP��ַ
#define SERVER_PORT  8000                          //�������˿ں�

void ESP8266_Init(void);             //��ͨ���ӷ�����

void Smartconfig(void);              //һ������


void ConnectServer(void);                        //���ӷ�����

#endif
