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



/********************************** 用户需要设置的参数**********************************/
#define      macUser_ESP8266_ApSsid                       "Tenda_A22AC0"               //要连接的热点的名称
#define      macUser_ESP8266_ApPwd                        "limutong@qq.com"            //要连接的热点的密码


//HTTP服务器IP及端口号
#define      macUser_ESP8266_TcpServer_IP                 "47.115.119.0"               //要连接的服务器的 IP
#define      macUser_ESP8266_TcpServer_Port               "3001"                       //要连接的服务器的端口





/********************************** 外部全局变量 ***************************************/
extern volatile uint8_t ucTcpClosedFlag;



/********************************** 测试函数声明 ***************************************/
void  ESP8266_Configuration(void);                               //透传前ESP8266配置
void  Reconnection(void);                                        //断线重连函数
void  ESP8266_StaTcpClient_UnvarnishTest  ( void );              //透传实现



#endif

