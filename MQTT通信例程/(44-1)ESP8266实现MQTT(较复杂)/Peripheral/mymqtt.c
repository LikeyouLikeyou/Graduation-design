#include "mymqtt.h"
#include "string.h"

//构建MQTT连接包 
u16 mqtt_connect_message(u8 *mqtt_message,char *client_id,char *username,char *password)
{
	u16 client_id_length = strlen(client_id);
	u16 username_length = strlen(username);
	u16 password_length = strlen(password);
	u16 packetLen;
	u16 i,baseIndex;
	
	packetLen = 12 + 2 + client_id_length;
	if(username_length > 0)
		packetLen = packetLen + 2 + username_length;
	if(password_length > 0)
		packetLen = packetLen+ 2 + password_length;
	
	mqtt_message[0] = 16;				//0x10 // MQTT Message Type CONNECT
	mqtt_message[1] = packetLen - 2;	//剩余长度(不包括固定头部)
	baseIndex = 2;
	if(packetLen > 127)
	{
		mqtt_message[2] = 1;			//packetLen/127;    
		baseIndex = 3;
	}
	mqtt_message[baseIndex++] = 0;		// Protocol Name Length MSB    
	mqtt_message[baseIndex++] = 4;		// Protocol Name Length LSB    
	mqtt_message[baseIndex++] = 77;		// ASCII Code for M    
	mqtt_message[baseIndex++] = 81;		// ASCII Code for Q    
	mqtt_message[baseIndex++] = 84;		// ASCII Code for T    
	mqtt_message[baseIndex++] = 84;		// ASCII Code for T    
	mqtt_message[baseIndex++] = 4;		// MQTT Protocol version = 4    
	mqtt_message[baseIndex++] = 0xc2;		// conn flags 
	mqtt_message[baseIndex++] = 0;		// Keep-alive Time Length MSB    
	mqtt_message[baseIndex++] = 60;		// Keep-alive Time Length LSB    
	mqtt_message[baseIndex++] = (0xff00&client_id_length)>>8;// Client ID length MSB    
	mqtt_message[baseIndex++] = 0xff&client_id_length;	// Client ID length LSB    
	
	// Client ID
	for(i = 0; i < client_id_length; i++)
	{
		mqtt_message[baseIndex + i] = client_id[i];    
	}
	baseIndex = baseIndex+client_id_length;
		
	if(username_length > 0)
	{
		//username    
		mqtt_message[baseIndex++] = (0xff00&username_length)>>8;//username length MSB    
		mqtt_message[baseIndex++] = 0xff&username_length;	//username length LSB    
		for(i = 0; i < username_length ; i++)
		{
			mqtt_message[baseIndex + i] = username[i];    
		}
		baseIndex = baseIndex + username_length;
	}
		
	if(password_length > 0)
	{
		//password    
		mqtt_message[baseIndex++] = (0xff00&password_length)>>8;//password length MSB    
		mqtt_message[baseIndex++] = 0xff&password_length;	//password length LSB    
		for(i = 0; i < password_length ; i++)
		{
			mqtt_message[baseIndex + i] = password[i];    
		}
		baseIndex += password_length; 
	}	
	
	return baseIndex;    
}
  
//构建MQTT发布消息包
u16 mqtt_publish_message(u8 *mqtt_message, char * topic, char * message, u8 qos)
{  
	u16 topic_length = strlen(topic);    
	u16 message_length = strlen(message);  
	u16 i,index=0;	
	static u16 id=0;
	
	mqtt_message[index++] = 48;	//0x30 // MQTT Message Type PUBLISH    
	if(qos)
		mqtt_message[index++] = 2 + topic_length + 2 + message_length;
	else
		mqtt_message[index++] = 2 + topic_length + message_length;   // Remaining length    
	mqtt_message[index++] = (0xff00&topic_length)>>8;
	mqtt_message[index++] = 0xff&topic_length;
		
	// Topic    
	for(i = 0; i < topic_length; i++)
	{
		mqtt_message[index + i] = topic[i];
	}
	index += topic_length;
		
	if(qos)
	{
		mqtt_message[index++] = (0xff00&id)>>8;
		mqtt_message[index++] = 0xff&id;
		id++;
	}
	
	// Message
	for(i = 0; i < message_length; i++)
	{
		mqtt_message[index + i] = message[i];
	}
	index += message_length;
		
	return index;
}

//构建MQTT发布确认包
//对QoS级别1的 PUBLISH 消息的回应
//当服务器发送 PUBLISH 消息给订阅者客户端，客户端回复 PUBACK 消息
u8 mqtt_puback_message(u8 *mqtt_message)
{
	static u16 id=0;
	
	mqtt_message[0] = 64;				//0x40 //消息类型和标志 PUBACK
	mqtt_message[1] = 2;				//剩余长度(不包括固定头部)
	mqtt_message[2] = (0xff00&id)>>8;	//消息标识符
	mqtt_message[3] = 0xff&id;			//消息标识符
	id++;
	
	return 4;
}
  
//构建MQTT订阅请求/取消订阅包
//whether=1,订阅; whether=0,取消订阅
u16 mqtt_subscribe_message(u8 *mqtt_message,char *topic,u8 qos,u8 whether)
{    
	u16 topic_len = strlen(topic);
	u16 i,index = 0;
	static u16 id=0;
	
	id++;
	if(whether)
		mqtt_message[index++] = 130;				//0x82 //消息类型和标志 SUBSCRIBE 订阅
	else
		mqtt_message[index++] = 162;				//0xA2 取消订阅
	mqtt_message[index++] = topic_len + 5;			//剩余长度(不包括固定头部)
	mqtt_message[index++] = (0xff00&id)>>8;			//消息标识符
	mqtt_message[index++] = 0xff&id;				//消息标识符
	mqtt_message[index++] = (0xff00&topic_len)>>8;	//主题长度(高位在前,低位在后)
	mqtt_message[index++] = 0xff&topic_len;			//主题长度 
	
	for (i = 0;i < topic_len; i++)
	{
		mqtt_message[index + i] = topic[i];
	}
	index += topic_len;
	
	if(whether)
	{
		mqtt_message[index] = qos;//QoS级别
		index++;
	}
	
	return index;
}

//构建MQTT PING请求包   心跳包
u8 mqtt_ping_message(u8 *mqtt_message)
{ 
	mqtt_message[0] = 192;	//0xC0 //消息类型和标志 PING
	mqtt_message[1] = 0;	//剩余长度(不包括固定头部)
	
	return 2;
}

//构建MQTT断开连接包
u8 mqtt_disconnect_message(u8 *mqtt_message)
{ 
	mqtt_message[0] = 224;	//0xE0 //消息类型和标志 DISCONNECT
	mqtt_message[1] = 0;	//剩余长度(不包括固定头部)
	
	return 2;
}

