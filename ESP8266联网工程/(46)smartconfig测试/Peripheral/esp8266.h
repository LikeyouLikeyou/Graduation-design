#ifndef __ESP8266_H_
#define __ESP8266_H_

#include <stdio.h>
#include <string.h>

#include "stm32f10x.h"
#include "usart1.h"
#include "usart3.h"
#include "delay.h"
#include "led.h"


#define SSID         "Tenda_A22AC0"                //热点名称
#define PWD          "limutong@qq.com"             //热点密码

#define TCP          "TCP"                         //协议
#define SERVER_IP    "106.54.47.12"                //服务器IP地址
#define SERVER_PORT  8000                          //服务器端口号

void ESP8266_Init(void);             //普通连接服务器

void Smartconfig(void);              //一键配网


void ConnectServer(void);                        //连接服务器

#endif
