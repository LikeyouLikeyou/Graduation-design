#ifndef __MQTT_H_
#define __MQTT_H_

#include "stm32f10x.h"
#include "delay.h"
#include "usart3.h"
#include <stdio.h>
#include <string.h>


#define BYTE0(dwTemp)       (*( char *)(&dwTemp))
#define BYTE1(dwTemp)       (*((char *)(&dwTemp) + 1))
#define BYTE2(dwTemp)       (*((char *)(&dwTemp) + 2))
#define BYTE3(dwTemp)       (*((char *)(&dwTemp) + 3))


typedef struct
{
	u8 *rxbuf;u16 rxlen;
	u8 *txbuf;u16 txlen;
	void (*Init)(u8 *prx,u16 rxlen,u8 *ptx,u16 txlen);
	u8 (*Connect)(char *ClientID,char *Username,char *Password);
	u8 (*SubscribeTopic)(char *topic,u8 qos,u8 whether);
	u8 (*PublishData)(char *topic, char *message, u8 qos);
	void (*SendHeart)(void);
	void (*Disconnect)(void);
}_typdef_mqtt;

extern _typdef_mqtt _mqtt;

void Mqtt_Progress(u8 *buf,u16 len);

#endif

