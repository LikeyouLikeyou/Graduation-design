#include "ESP8266.h"
#include "mqtt.h"

uint8_t sta=0;

/* MQTT参数 */
#define CLIENT_ID   "12345|securemode=3,signmethod=hmacsha1,timestamp=123|"    //客户机ID
#define USERNAME    "allall&a14RblHTlyK"                               //用户名
#define PASSWORD    "A2F39ED675826036C411AFEBCDD0C01A8AD50D6E"                 //密码


//注意：要想将接受的数据解析就要将USART3->DR寄存器中的数据拿出来，其实就是去看串口3的中断处理函数，
//中断服务函数中就可以看出来将接收到的数据存入到了rxbuf中了，所以我们要解析服务器发来的数据就只要
//将rxbuf中的数据解析就行了

//用来采集传感器数据
//char mqtt_message[200];
//sprintf(mqtt_message,);


void Login_ESP8266_Subscribe_Data(void)
{
    //检查ESP8266
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
        //连接热点
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
        //连接TCP，并且开启透传
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
        //登录MQTT
        _mqtt.Init(rxbuf,sizeof(rxbuf),txbuf,sizeof(txbuf));
//        if(_mqtt.Connect("Client","admin","public") != 0)                                                      //Client,Username，Password

//        {
//            printf("Enter MQTT OK!\r\n");
//            sta++;
//        }
//        else
//        {
//            printf("Enter MQTT Error!\r\n");
//            sta=0;
//        }
			  if(_mqtt.Connect(CLIENT_ID,USERNAME,PASSWORD) != 0)                                                      //Client,Username，Password
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
        //订阅主题
        if(_mqtt.SubscribeTopic("/mqtt/topic/1",0,1) != 0)    //tpoic,qos,是否订阅
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
        if(++cnt_5s>=3000)                                                  //这里是30秒推送一次消息给服务器
        {
            cnt_5s=0;
            _mqtt.PublishData("/mqtt/topic/0","Hello,Server",0);            //推送数据
        }
				
        if(_mqtt.rxlen)         //清空接收缓存
        {
            Mqtt_Progress(_mqtt.rxbuf,_mqtt.rxlen);                         //这一句只会执行一次
					  memset(_mqtt.rxbuf,0,_mqtt.rxlen);
            _mqtt.rxlen = 0;
        }
        delay_ms(10);
    }
}




