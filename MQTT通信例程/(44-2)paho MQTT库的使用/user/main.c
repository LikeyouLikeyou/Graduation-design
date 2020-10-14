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
    Timer_init(59999,7199);                         //60S发送一次心跳包

    ESP8266_Init();                                 //ESP8266初始化

    /* 连接MQTT服务器 */
    if(!MQTT_Connect(CLIENTID,USERNAME,USERPWD))                             //连接服务器
    {
        printf("MQTT Connect is OK!\r\n");
        if(!MQTT_Subscrib("/mqtt/test",0))                //订阅消息,QOS=0
        {
            printf("MQTT Sub is OK!\r\n");
        }
    }


    while(1)
    {
        if(!MQTT_Publish("test","123456",0))            //发布消息,QOS=0
        {
            printf("MQTT Pub is OK!\r\n");
        }

        delay_ms(1000);
    }
}




