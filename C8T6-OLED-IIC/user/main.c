#include "oled.h"
#include "printf.h"
#include "delay.h"

int main(void)
{
	  USART_Initialization(115200);
    OLED_Init();			//��ʼ��OLED
    OLED_Clear();
	  printf("OLED Init is OK!\r\n");
    while(1)
    {
			  /* �¶� */
			  OLED_ShowString(0,0,"Tem:",8);   //������
			  /* ʪ�� */
			  OLED_ShowString(0,1,"Hum:",8);   //������	
			  /* PM2.5 */
			  OLED_ShowString(0,2,"PM2.5:",8);   //������
			  /* �к����� */
			  OLED_ShowString(0,3,"Harm:",8);   //������
			
			  delay_ms(1000);
    }
}



