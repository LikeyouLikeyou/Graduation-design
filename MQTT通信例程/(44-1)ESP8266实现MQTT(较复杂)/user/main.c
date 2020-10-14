#include "mymqtt.h"
#include "esp826601s.h"
#include "printf.h"
#include "delay.h"
#include "usart3.h"
#include "timer.h"
#include <string.h>

u8 mqtt_msg[200]={0};
u16 len;

const u8 connetAck[] = {0x20,0x02,0x00,0x00};       //����ȷ��
const u8 subAck[] = {0x90,0x03};                    //����ȷ��

void Mqtt_Init(void)
{
	u8 delay_nms;
	
	ESP826601S_Init();
	
	/* MQTTa���� */
	len=mqtt_connect_message(mqtt_msg,"123456","admin","public");//id=123456,�û���������Ϊ��
	Usart3_SendBuf(mqtt_msg,len);                       //�������Ӱ�
	delay_nms=30;//�ȴ�3sʱ��
	while((rxbuf[0]!=connetAck[0] && rxbuf[1]!=connetAck[1]) && delay_nms--)
	{
			delay_ms(100);
	}
	printf("\r\nMQTT_Connect Successful\r\n");
	
	
	/* MQTT���� */
	memset(rxbuf,0,256);                                //��ս��ջ�����
  memset(mqtt_msg,0,200);  	                          //��շ��Ͱ�������
  len=mqtt_subscribe_message(mqtt_msg,"test",0,1);    //����test����
	Usart3_SendBuf(mqtt_msg,len);                       //�������Ӱ�
	delay_nms=30;//�ȴ�3sʱ��
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
	Mqtt_Init();                                       //MQTT��ESP8266��ʼ��
  Timer_init(59999,7199);                            //60S��һ��������
	while(1)
	{
		/* ������Ϣ */
		memset(rxbuf,0,256);                                //��ս��ջ�����
    memset(mqtt_msg,0,200);  	                          //��շ��Ͱ�������
    len=mqtt_publish_message(mqtt_msg,"/mqtt/test", "45.3",0);
	  Usart3_SendBuf(mqtt_msg,len);                       //���ͷ�����	
		delay_ms(1500);
		delay_ms(1500);
	}
}
