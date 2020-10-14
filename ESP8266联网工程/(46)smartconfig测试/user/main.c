#include "esp8266.h"
#include "keypros.h"

int main()
{
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    Usart1_Configuration(115200);
    Usart3_Configuration(115200);
	  key_pros_Init();  //按键初始化函数
	  LED_Init();
    delay_ms(200);
    ConnectServer();          //连接服务器
    while(1)
    {
			if(key_wk_up_press==key_scan(0))                //这里应该把按键按下放到外部中断里面去这样只有完成配网才会来执行发送
			{
				Smartconfig();            //ESP-TOUCH配置
			}
			delay_ms(1000);   //延时毫秒
			Usart3_SendString("Hello,word!\r\n");
    }
}


