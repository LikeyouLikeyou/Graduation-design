#ifndef __MYMQTT_H_
#define __MYMQTT_H_

#include "stm32f10x.h"

u16 mqtt_connect_message(u8 *mqtt_message,char *client_id,char *username,char *password);
u16 mqtt_publish_message(u8 *mqtt_message, char * topic, char * message, u8 qos);
u8 mqtt_puback_message(u8 *mqtt_message);
u16 mqtt_subscribe_message(u8 *mqtt_message,char *topic,u8 qos,u8 whether);
u8 mqtt_ping_message(u8 *mqtt_message);
u8 mqtt_disconnect_message(u8 *mqtt_message);


#endif
