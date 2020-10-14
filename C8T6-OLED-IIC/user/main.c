#include "oled.h"
#include "printf.h"
#include "delay.h"

int main(void)
{
	  USART_Initialization(115200);
    OLED_Init();			//初始化OLED
    OLED_Clear();
	  printf("OLED Init is OK!\r\n");
    while(1)
    {
			  /* 温度 */
			  OLED_ShowString(0,0,"Tem:",8);   //第三行
			  /* 湿度 */
			  OLED_ShowString(0,1,"Hum:",8);   //第三行	
			  /* PM2.5 */
			  OLED_ShowString(0,2,"PM2.5:",8);   //第三行
			  /* 有害气体 */
			  OLED_ShowString(0,3,"Harm:",8);   //第三行
			
			  delay_ms(1000);
    }
}



