#include "test.h"


volatile uint8_t ucTcpClosedFlag = 0;

//char cStr [ 1500 ] = { 0 };         //发送缓存


/*
  *****************************************************************************
  * @Name   : ESP8266_Configuration(void)
  *
  * @Brief  : 主要做透传前的连接路由器和服务器工作
  *
  * @Input  : none
  *
  * @Output : none
  *
  * @Return : none
  *****************************************************************************
 */
void ESP8266_Configuration(void)
{
    printf ( "\r\n正在配置 ESP8266 ......\r\n" );

    macESP8266_CH_ENABLE();               //运行时，外部拉高烧写程序或固件时外部拉低

    ESP8266_AT_Test ();                   //测试AT

    ESP8266_Net_Mode_Choose ( STA );      //选择为STA模式

    while ( ! ESP8266_JoinAP ( macUser_ESP8266_ApSsid, macUser_ESP8266_ApPwd ) );        //连路由器

    ESP8266_Enable_MultipleId ( DISABLE );                                               //作为客户端我们这里失能多连接

    while ( !	ESP8266_Link_Server ( enumTCP, macUser_ESP8266_TcpServer_IP, macUser_ESP8266_TcpServer_Port, Single_ID_0 ) );     //连接服务器

    while ( ! ESP8266_UnvarnishSend () );             //开启透传

    printf ( "\r\n配置 ESP8266 完毕\r\n" );
}

/*
  *****************************************************************************
  * @Name   : void Reconnection(void)
  *
  * @Brief  : 断线重连函数，主要实现客户机断线重连
  *
  * @Input  : none
  *
  * @Output : none
  *
  * @Return : none
  *****************************************************************************
 */
void Reconnection(void)
{
    uint8_t ucStatus;

    if ( ucTcpClosedFlag )                                             //检测是否失去连接
    {
        ESP8266_ExitUnvarnishSend ();                                    //退出透传模式

        do ucStatus = ESP8266_Get_LinkStatus ();                         //获取连接状态
        while ( ! ucStatus );

        if ( ucStatus == 4 )                                             //确认失去连接后重连
        {
            printf ( "\r\n正在重连热点和服务器 ......\r\n" );

            while ( ! ESP8266_JoinAP ( macUser_ESP8266_ApSsid, macUser_ESP8266_ApPwd ) );

            while ( !	ESP8266_Link_Server ( enumTCP, macUser_ESP8266_TcpServer_IP, macUser_ESP8266_TcpServer_Port, Single_ID_0 ) );

            printf ( "\r\n重连热点和服务器成功\r\n" );

        }

        while ( ! ESP8266_UnvarnishSend () );

    }
}

//void Smartconfig(void)                            //智能配网，还没有写好
//{
//	
//			  /*************退出透传关闭TCP连接方便下次重连*******/

//			  if(key_scan(0)==key_wk_up_press)      //如果wk_up按下则退出透传模式
//				{
//			    ESP8266_ExitUnvarnishSend ();      //退出透传
//					ESP8266_ExitLink();                //关闭TCP连接
//					printf("退出透传成功！关闭连接成功！\r\n");
//			  }

//				/*************************************************/
//	
//}


/**
  * @brief  ESP8266 （Sta Tcp Client）透传
  * @param  无
  * @retval 无
  */
void ESP8266_StaTcpClient_UnvarnishTest ( void )
{
    char cStr [ 256 ] = { 0 };       //发送缓存

//		int result; 
		
//		char *p=NULL;
		
    ESP8266_Configuration();         //配置为透传
		
		
    while ( 1 )
    {

        CreateJsonData();      			//创建JSON数据

        sprintf ( cStr,POST,strlen(JSON_Data_Buff),JSON_Data_Buff);          //发送POST请求
//			  sprintf ( cStr,GET,GET_HTTPURL,HOST);  //发送GET请求

        ESP8266_SendString ( ENABLE, cStr, 0, Single_ID_0 );                 //发送数据

			
        delay_ms ( 1000 );                                                   //3S重发一次GET请求
			
			  printf("发送POST成功!\r\n");
//			  delay_ms ( 1000 );                                                 //3S重发一次GET请求
//			  delay_ms ( 1000 );                                                 //3S重发一次GET请求

//			  p = (char *)strstr(ESP8266_ReceiveString(ENABLE), "\r\n\r\n") + strlen("\r\n\r\n");
			
//			  result=ParseJsonData(p);
//			  printf("%d\r\n",result);
//        printf("%s\r\n",ESP8266_ReceiveString(ENABLE));                    //将接收收的数据通过串口1打印出来,这里如果要打印的话要写在延时后面，要不然太快导致打印不出数据，实际上是收到了

        Reconnection();             //断线重连机制
    }
}


