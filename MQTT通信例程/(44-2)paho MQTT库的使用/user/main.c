#include "mymqtt.h"
#include "usart3.h"
#include "printf.h"
#include "delay.h"
#include "esp8266.h"
#include "timer.h"


int main(void)
{
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    USART_Initialization(115200);
    Usart3_Configuration(115200);
    Timer_init(59999,7199);                         //60S����һ��������

    ESP8266_Init();                                 //ESP8266��ʼ��

    /* ����MQTT������ */
    if(!MQTT_Connect(CLIENTID,USERNAME,USERPWD))                             //���ӷ�����
    {
        printf("MQTT Connect is OK!\r\n");
        if(!MQTT_Subscrib("/mqtt/test",0))                //������Ϣ,QOS=0
        {
            printf("MQTT Sub is OK!\r\n");
        }
    }


    while(1)
    {
        if(!MQTT_Publish("test","123456",0))            //������Ϣ,QOS=0
        {
            printf("MQTT Pub is OK!\r\n");
        }

        delay_ms(1000);
    }
}




