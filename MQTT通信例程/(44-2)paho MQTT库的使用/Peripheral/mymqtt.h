#ifndef __MYMQTT_H_
#define __MYMQTT_H_

#include "stm32f10x.h"

/* �ͻ���ID���û��������� */
#define CLIENTID  "client"
#define USERNAME  "admin"
#define USERPWD   "public"

/* ����MQTT������ */
u8 MQTT_Connect(char *clientid,char *username,char *userpwd);

/* ������Ϣ */
u8 MQTT_Publish(char *pTopic,char *pMessage,int QOS);

/* ������Ϣ */
u8 MQTT_Subscrib(char *pTopic,int QOS);


#endif
