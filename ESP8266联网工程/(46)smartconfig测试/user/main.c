#include "esp8266.h"
#include "keypros.h"

int main()
{
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    Usart1_Configuration(115200);
    Usart3_Configuration(115200);
	  key_pros_Init();  //������ʼ������
	  LED_Init();
    delay_ms(200);
    ConnectServer();          //���ӷ�����
    while(1)
    {
			if(key_wk_up_press==key_scan(0))                //����Ӧ�ðѰ������·ŵ��ⲿ�ж�����ȥ����ֻ����������Ż���ִ�з���
			{
				Smartconfig();            //ESP-TOUCH����
			}
			delay_ms(1000);   //��ʱ����
			Usart3_SendString("Hello,word!\r\n");
    }
}


