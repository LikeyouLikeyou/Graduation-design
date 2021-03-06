#include "usart1.h"
#include "usart3.h"
#include "delay.h"
#include <stdio.h>
#include <string.h>

#define SSID         "Tenda_A22AC0"                //热点名称
#define PWD          "limutong@qq.com"             //热点密码

#define TCP          "TCP"                         //协议
#define SERVER_IP    "106.54.47.12"                //服务器IP地址
#define SERVER_PORT  8000                          //服务器端口号


u8 sta=0;

u8 FindStr(char* dest,char* src,u16 retry_nms)
{
    retry_nms/=10;                   //超时时间

    while(strstr(dest,src)==0 && retry_nms--)     //等待串口接收完毕或超时退出，因为当strstr找到字符串时便会返回地址使while不成立于是跳出
    {
        delay_ms(10);
    }

    if(retry_nms)                      //上面 retry_nms减到0跳出while时这里会变成0xFFFF
			return 1;

    return 0;
}

static u8 Check(void)
{
    u8 check_cnt=5;
    while(check_cnt--)
    {
        memset(rxbuf,0,256);
        Usart3_SendString("AT\r\n");
        if(FindStr((char*)rxbuf,"OK",200) != 0)
        {
            return 1;
        }
    }
    return 0;
}

static u8 Close(void)
{
    memset(rxbuf,0,256);
    Usart3_SendString("ATE0\r\n");
    if(FindStr((char*)rxbuf,"OK",500)==0)  //设置不成功
    {
        return 0;
    }
    else
    {
        return 1;
    }
}

static u8 Station(void)
{
    /* 连接AP */
    memset(rxbuf,0,256);
    Usart3_SendString("AT+CWMODE_CUR=1\r\n");
    if(FindStr((char*)rxbuf,"OK",200) != 0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

static u8 ConAP(void)
{
    memset(rxbuf,0,256);
    sprintf((char*)txbuf,"AT+CWJAP_CUR=\"%s\",\"%s\"\r\n",SSID,PWD);//连接目标AP
    Usart3_SendString((char*)txbuf);
    if(FindStr((char*)rxbuf,"OK",8000)!=0)                      //连接成功且分配到IP
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

static u8 Opensend(void)
{
    /* 开启透传 */
    memset(rxbuf,0,256);
    Usart3_SendString("AT+CIPSEND\r\n");//开始处于透传发送状态
    if(FindStr((char*)rxbuf,">",200)!=0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

static u8 Conserver()
{
    /* 连接服务器 */
    Usart3_SendString("+++");
    delay_ms(50);
    Usart3_SendString("+++");
    delay_ms(50);
    delay_ms(500);
    memset(rxbuf,0,256);
    sprintf((char*)txbuf,"AT+CIPSTART=\"%s\",\"%s\",%d\r\n",TCP,SERVER_IP,SERVER_PORT);
    Usart3_SendString((char*)txbuf);
    if(FindStr((char*)rxbuf,"CONNECT",8000) !=0 )
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

static u8 Setsend(void)
{
    /* 设置透传 */
    memset(rxbuf,0,256);
    Usart3_SendString("AT+CIPMODE=1\r\n");
    if(FindStr((char*)rxbuf,"OK",200)!=0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

void ESP8266_Init(void)
{
    /* 初始化 */
    memset(rxbuf,0,256);
    memset(txbuf,0,256);
    Usart3_SendString("+++");
    delay_ms(50);
    Usart3_SendString("+++");
    delay_ms(50);
    delay_ms(500);
    Usart3_SendString("AT+RST\r\n");
    delay_ms(800);

//	  while(!Check()){};             //使用AT指令检查ESP8266是否存在
//	  while(!Close()){};             //使用AT指令检查ESP8266是否存在
//		while(!Station()){};	         //配置为station
//		while(!ConAP()){};             //连接热点
//		while(!Conserver()){};         //连接服务器
//		while(!Setsend()){};           //设置透传模式
//		while(!Opensend()){};          //开启透传	
	
    if(sta==0)
    {
        if(Check()==1)              //使用AT指令检查ESP8266是否存在
        {
            sta++;
        }
        else
        {
            sta=0;
        }
    }

    if(sta==1)
    {
        if(Close()==1)              //使用AT指令检查ESP8266是否存在
        {
            sta++;
        }
        else
        {
            sta=0;
        }
    }

    if(sta==2)
    {
        if(Station()==1)              //配置为station
        {
            sta++;
        }
        else
        {
            sta=0;
        }
    }

    if(sta==3)
    {
        if(ConAP()==1)              //连接热点
        {
            sta++;
        }
        else
        {
            sta=0;
        }
    }

    if(sta==4)
    {
        if(Conserver()==1)              //连接服务器
        {
            sta++;
        }
        else
        {
            sta=0;
        }
    }


    if(sta==5)
    {
        if(Setsend()==1)              //设置透传模式
        {
            sta++;
        }
        else
        {
            sta=0;
        }
    }


    if(sta==6)
    {
        if(Opensend()==1)              //开启透传模式
        {
            sta++;
        }
        else
        {
            sta=0;
        }
    }
}

/**
* 介绍:  主函数
* 说明:  每间隔1S发送一次温湿度数据
* 说明:  返回串口接收到的数据,发送方式为中断发送
* 说明:  None
**/



int main()
{
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    Usart1_Configuration(115200);
    Usart3_Configuration(115200);
    delay_ms(200);
    ESP8266_Init();
    while(1)
    {
        delay_ms(1000);   //延时毫秒
        Usart3_SendString("Hello,word!\r\n");
    }
}


