#include "esp8266.h"


static uint8_t AT_Set(char* buff,char* src,u16 retry_nms)
{
    memset(rxbuf,0,256);
    Usart3_SendString(buff);         //发送AT指令

    retry_nms/=10;                   //超时时间
    while(strstr((char*)rxbuf,src)==0 && retry_nms--)     //等待串口接收完毕或超时退出，因为当strstr找到字符串时便会返回地址使while不成立于是跳出
    {
        delay_ms(10);
    }

    if(retry_nms)                      //上面 retry_nms减到0跳出while时这里会变成0xFFFF
        return 1;

    return 0;
}

void Smartconfig(void)                   //smartconfig配置
{
    uint8_t sta=0;

    /* 退出透传 */
    Usart3_SendString("+++");
    delay_ms(50);
    Usart3_SendString("+++");
    delay_ms(50);
    delay_ms(500);

    /* 复位 */
    Usart3_SendString("AT+RST\r\n");
    delay_ms(800);

    if(sta==0)              //恢复出厂设置
    {
        if(AT_Set("AT+RESTORE\r\n","ready",800)==1)
        {
            sta++;
        }
        else
        {
            sta=0;
        }
    }

    if(sta==1)              //关闭回显
    {
        if(AT_Set("ATE0\r\n","OK",500)==1)
        {
            sta++;
        }
        else
        {
            sta=0;
        }
    }

    if(sta==2)              //设置当前 Wi-Fi 模式并保存到 Flash，这里设置为station模式
    {
        if(AT_Set("AT+CWMODE_DEF=1\r\n","OK",200)==1)
        {
            sta++;
        }
        else
        {
            sta=0;
        }
    }

    if(sta==3)              //上电是否?自动连接，这里配置为上电自动连接路由器
    {
        if(AT_Set("AT+CWAUTOCONN=1\r\n","OK",200)==1)
        {
            sta++;
        }
        else
        {
            sta=0;
        }
    }

    if(sta==4)              //开启smartconfig，这里配置为ESP-TOUCH
    {
        if(AT_Set("AT+CWSTARTSMART=1\r\n","OK",500)==1)
        {
            sta++;
        }
        else
        {
            sta=0;
        }
    }

    /* 等待配网成功 */
    memset(rxbuf,0,256);
    while(strstr((char*)rxbuf,"smartconfig connected wifi")==0) {}  //等待15S
    GPIO_ResetBits(GPIOE,GPIO_Pin_5);                               //配置成功会点亮LED

    if(sta==5)              //关闭配网
    {
        AT_Set("AT+CWSTOPSMART\r\n","OK",200);
    }
}

void ConnectServer(void)                        //连接服务器
{
    uint8_t sta=0;
    memset(rxbuf,0,256);

    /* 复位 */
	  Usart3_SendString("AT+RST\r\n");
    delay_ms(800);
	  Usart3_SendString("+++");
    delay_ms(50);
    Usart3_SendString("+++");
    delay_ms(50);
 //   delay_ms(500);


    if(sta==0)
    {
        if(AT_Set("ATE0\r\n","OK",500)!=0)	//关闭回显
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
        /* 连接服务器 */
				delay_ms(500);
        memset(txbuf,0,256);
        sprintf((char*)txbuf,"AT+CIPSTART=\"%s\",\"%s\",%d\r\n",TCP,SERVER_IP,SERVER_PORT);
        Usart3_SendString((char*)txbuf);
        if(AT_Set((char*)txbuf,"CONNECT",8000) !=0 )
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
        /* 配置为透传 */
        if(AT_Set("AT+CIPMODE=1\r\n","OK",200)!=0)
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
        /* 开启透传 */
        if(AT_Set("AT+CIPSEND\r\n",">",200)!=0)
        {
            printf("Start Send!\r\n");
        }
        else
        {
            printf("Start Send ERROR!\r\n");
        }
    }
}
