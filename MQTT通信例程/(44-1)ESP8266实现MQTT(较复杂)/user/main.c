#include "mymqtt.h"
#include "esp826601s.h"
#include "printf.h"
#include "delay.h"
#include "usart3.h"
#include "timer.h"
#include <string.h>

u8 mqtt_msg[200]={0};
u16 len;

const u8 connetAck[] = {0x20,0x02,0x00,0x00};       //连接确认
const u8 subAck[] = {0x90,0x03};                    //订阅确认

void Mqtt_Init(void)
{
	u8 delay_nms;
	
	ESP826601S_Init();
	
	/* MQTTa连接 */
	len=mqtt_connect_message(mqtt_msg,"123456","admin","public");//id=123456,用户名和密码为空
	Usart3_SendBuf(mqtt_msg,len);                       //发送连接包
	delay_nms=30;//等待3s时间
	while((rxbuf[0]!=connetAck[0] && rxbuf[1]!=connetAck[1]) && delay_nms--)
	{
			delay_ms(100);
	}
	printf("\r\nMQTT_Connect Successful\r\n");
	
	
	/* MQTT订阅 */
	memset(rxbuf,0,256);                                //清空接收缓存区
  memset(mqtt_msg,0,200);  	                          //清空发送包缓存区
  len=mqtt_subscribe_message(mqtt_msg,"test",0,1);    //订阅test主题
	Usart3_SendBuf(mqtt_msg,len);                       //发送连接包
	delay_nms=30;//等待3s时间
	while((rxbuf[0]!=subAck[0] && rxbuf[1]!=subAck[1]) && delay_nms--)
	{
			delay_ms(100);
	}
	printf("\r\nSubscribe Successful\r\n");
}



int main(void)
{
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	Usart3_Configuration(115200);
	USART_Initialization(115200);
	Mqtt_Init();                                       //MQTT和ESP8266初始化
  Timer_init(59999,7199);                            //60S发一次心跳包
	while(1)
	{
		/* 发布消息 */
		memset(rxbuf,0,256);                                //清空接收缓存区
    memset(mqtt_msg,0,200);  	                          //清空发送包缓存区
    len=mqtt_publish_message(mqtt_msg,"/mqtt/test", "45.3",0);
	  Usart3_SendBuf(mqtt_msg,len);                       //发送发布包	
		delay_ms(1500);
		delay_ms(1500);
	}
}
