#include "mymqtt.h"
#include "MQTTPacket.h"
#include "usart3.h"
#include "delay.h"
#include <string.h>

static unsigned char buf[200]= {0};

const u8 connetAck[] = {0x20,0x02,0x00,0x00};       //连接确认
const u8 subAck[] = {0x90,0x03};                    //订阅确认

/**
  * @brief  连接代理（服务器）
  * @param  clientid:客户机ID
  *         username：用户名
  *         userpwd：密码
  *
  * @param  none
  * @retval 0表示连接成功
  */
u8 MQTT_Connect(char *clientid,char *username,char *userpwd)
{
    u32 len;
//	u32 i;
    u8 delay_nms;
    MQTTPacket_connectData data = MQTTPacket_connectData_initializer;

    data.clientID.cstring = clientid;
    data.keepAliveInterval = 60;	             //60秒发送一次心跳包
    data.cleansession = 1;                     //清除会话
    data.username.cstring = username;		       // 用户名
    data.password.cstring = userpwd;  	       // 密码
    len = MQTTSerialize_connect(buf, sizeof(buf), &data);

    printf("len=%d\r\nMQTTPacket_connectData\r\n",len);

//	/* 检查连接包 */
//	for(i=0;i<len;i++)
//	{
//		printf("%02x ",buf[i]);
//	}

    Usart3_SendBuf(buf,len);
    delay_nms=30;                              //等待3s时间
    while((rxbuf[0]!=connetAck[0] && rxbuf[1]!=connetAck[1]) && --delay_nms)
    {
        delay_ms(100);
    }
    memset(rxbuf,0,256);                       //清空接收缓存区
    if(delay_nms) return 0;

    return 1;
}

/**
  * @brief  向代理（服务器）发送一个消息
  * @param  pTopic 消息主题
  * @param  pMessage 消息内容
  * @retval 0表示发送成功
  */
u8 MQTT_Publish(char *pTopic,char *pMessage,int QOS)
{
    MQTTString topicString = MQTTString_initializer;
    u16 msglen = strlen(pMessage);
    u16 buflen = sizeof(buf);
    u16 len;

    topicString.cstring = pTopic;
    len = MQTTSerialize_publish(buf, buflen, 0, QOS, 0, 0, topicString, (unsigned char*)pMessage, msglen); /* qos=0 */

    Usart3_SendBuf(buf,len);

    return 0;
}

/**
  * @brief  向服务器订阅一个消息
  * @param  pTopic 消息主题，传入
  * @retval 0表示订阅消息成功
  */
u8 MQTT_Subscrib(char *pTopic,int QOS)
{
    MQTTString topicString = MQTTString_initializer;
    u16 buflen = sizeof(buf);
    u16 msgid = 1;
    int req_qos = QOS;                      //QOS=0
    int len = 0;
    u8 delay_nms;

    topicString.cstring = pTopic;
    len = MQTTSerialize_subscribe(buf, buflen, 0, msgid, 1, &topicString, &req_qos);

    Usart3_SendBuf(buf,len);
    delay_nms=30;                          //等待3s时间
    while((rxbuf[0]!=subAck[0] && rxbuf[1]!=subAck[1]) && --delay_nms)
    {
        delay_ms(100);
    }
    memset(rxbuf,0,256);                  //清空接收缓存区
    if(delay_nms) return 0;

    return 1;
}

