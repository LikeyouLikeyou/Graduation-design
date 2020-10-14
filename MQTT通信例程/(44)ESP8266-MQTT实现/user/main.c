#include "ESP8266.h"
#include "mqtt.h"

uint8_t sta=0;

/* MQTT���� */
#define CLIENT_ID   "12345|securemode=3,signmethod=hmacsha1,timestamp=123|"    //�ͻ���ID
#define USERNAME    "allall&a14RblHTlyK"                               //�û���
#define PASSWORD    "A2F39ED675826036C411AFEBCDD0C01A8AD50D6E"                 //����


//ע�⣺Ҫ�뽫���ܵ����ݽ�����Ҫ��USART3->DR�Ĵ����е������ó�������ʵ����ȥ������3���жϴ�������
//�жϷ������оͿ��Կ����������յ������ݴ��뵽��rxbuf���ˣ���������Ҫ�������������������ݾ�ֻҪ
//��rxbuf�е����ݽ���������

//�����ɼ�����������
//char mqtt_message[200];
//sprintf(mqtt_message,);


void Login_ESP8266_Subscribe_Data(void)
{
    //���ESP8266
    if(_net.Init(rxbuf,sizeof(rxbuf),txbuf,sizeof(txbuf))!=0)
    {
        printf("Net Init OK!\r\n");
        sta++;
    }
    else
    {
        printf("Net Init Error!\r\n");
        sta=0;
    }

    if(sta==1)
    {
        //�����ȵ�
        if(_net.ConnectAP(SSID,PWD)!=0)
        {

            printf("Conncet AP OK!\r\n");
            sta++;
        }
        else
        {
            printf("Conncet AP Error!\r\n");
            sta=0;
        }
    }

    if(sta==2)
    {
        //����TCP�����ҿ���͸��
        if(_net.ConnectServer(TCP,IP,PORT)!=0)
        {
            printf("Conncet Server OK!\r\n");
            sta++;
        }
        else
        {
            printf("Conncet Server Error!\r\n");
            sta=0;
        }
    }

    if(sta==3)
    {
        //��¼MQTT
        _mqtt.Init(rxbuf,sizeof(rxbuf),txbuf,sizeof(txbuf));
//        if(_mqtt.Connect("Client","admin","public") != 0)                                                      //Client,Username��Password

//        {
//            printf("Enter MQTT OK!\r\n");
//            sta++;
//        }
//        else
//        {
//            printf("Enter MQTT Error!\r\n");
//            sta=0;
//        }
			  if(_mqtt.Connect(CLIENT_ID,USERNAME,PASSWORD) != 0)                                                      //Client,Username��Password
        {
            printf("Enter MQTT OK!\r\n");
            sta++;
        }
        else
        {
            printf("Enter MQTT Error!\r\n");
            sta=0;
        }
				
    }

    if(sta==4)
    {
        //��������
        if(_mqtt.SubscribeTopic("/mqtt/topic/1",0,1) != 0)    //tpoic,qos,�Ƿ���
        {
            printf("SubscribeTopic OK!\r\n");
        }
        else
        {
            printf("SubscribeTopic Error!\r\n");
        }
    }
}




int main()
{
    u16 cnt_5s=0;
	
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    Usart1_Configuration(115200);
    Usart3_Configuration(115200);
    Usart1_SendString("usart1 is ok!\r\n");
    delay_ms(200);

    Login_ESP8266_Subscribe_Data();

	  sta=0;
	
    while(1)
    {
        if(++cnt_5s>=3000)                                                  //������30������һ����Ϣ��������
        {
            cnt_5s=0;
            _mqtt.PublishData("/mqtt/topic/0","Hello,Server",0);            //��������
        }
				
        if(_mqtt.rxlen)         //��ս��ջ���
        {
            Mqtt_Progress(_mqtt.rxbuf,_mqtt.rxlen);                         //��һ��ֻ��ִ��һ��
					  memset(_mqtt.rxbuf,0,_mqtt.rxlen);
            _mqtt.rxlen = 0;
        }
        delay_ms(10);
    }
}




