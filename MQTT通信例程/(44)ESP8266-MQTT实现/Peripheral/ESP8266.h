#ifndef   __ESP8266_H_
#define  __ESP8266_H_

#include "stm32f10x.h"
#include "usart3.h"
#include "usart1.h"
#include "delay.h"
#include <stdio.h>
#include <string.h>

/*连接AP宏定义*/
#define SSID "Tenda_A22AC0"
#define PWD  "limutong@qq.com"

/*连接服务器宏定义*/
//#define TCP "TCP"
//#define UDP "UDP"
//#define IP  "106.54.47.12"
//#define PORT 1883
#define TCP "TCP"
#define UDP "UDP"
#define IP  "a14RblHTlyK.iot-as-mqtt.cn-shanghai.aliyuncs.com"
#define PORT 1883


#define Net_SendString(str)  Usart3_SendString(str)
#define Net_SendBuf(buf,len) Usart3_SendBuf(buf,len)

/* 此结构体内除去开头的四个外，其他均为函数指针  */
typedef struct
{
	u8 *rxbuf;u16 rxlen;
	u8 *txbuf;u16 txlen;
	
	u8 (*Check)(void);
	u8 (*Init)(u8 *prx,u16 rxlen,u8 *ptx,u16 txlen);
	void (*Restore)(void);
	u8 (*ConnectAP)(char *ssid,char *pswd);
	u8 (*ConnectServer)(char* mode,char *ip,u16 port);
	u8 (*DisconnectServer)(void);
	u8 (*OpenTransmission)(void);
	void (*CloseTransmission)(void);		
	void (*SendString)(char *str);
	void (*SendBuf)(u8 *buf,u16 len);
}_typdef_net;

extern _typdef_net _net;

#endif

/*********************************************END OF FILE********************************************/

