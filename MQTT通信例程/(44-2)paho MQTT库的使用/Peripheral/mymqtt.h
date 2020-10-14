#ifndef __MYMQTT_H_
#define __MYMQTT_H_

#include "stm32f10x.h"

/* 客户机ID，用户名，密码 */
#define CLIENTID  "client"
#define USERNAME  "admin"
#define USERPWD   "public"

/* 连接MQTT服务器 */
u8 MQTT_Connect(char *clientid,char *username,char *userpwd);

/* 发布消息 */
u8 MQTT_Publish(char *pTopic,char *pMessage,int QOS);

/* 订阅消息 */
u8 MQTT_Subscrib(char *pTopic,int QOS);


#endif
