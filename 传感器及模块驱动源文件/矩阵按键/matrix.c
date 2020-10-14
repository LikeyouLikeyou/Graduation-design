#include "matrix.h"



/*    ����˵��  */
/*
      PB12����C1
			PB13����C2
			PB14����C3
			PB15����C4

			PB5����R1
			PB6����R2
			PB7����R3
			PB8����R4
*/

uint8_t relayms=50;

/*
  *****************************************************************************
  * @Name   : ���󰴼�GPIO��ʼ������
  *
  * @Brief  :
 	*           �ް���������ʱ��PB5 - PB8 Ϊ0��Ϊ�͵�ƽ״̬
  *           �а���������ʱ��PA5 - PA2 ��Ӧ��������ʾΪ�ߵ�ƽ
  *
  * @Input  : none
  *
  * @Output : none
  *
  * @Return : none
  *****************************************************************************
 */
void Matrix_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStruction;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);

    /* �� */
    GPIO_InitStruction.GPIO_Mode=GPIO_Mode_Out_PP;                                //�������
    GPIO_InitStruction.GPIO_Pin=GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15;      //PB��12��13��14��15  C1��C2��C3��C4
    GPIO_InitStruction.GPIO_Speed=GPIO_Speed_50MHz;
    GPIO_Init(GPIOB,&GPIO_InitStruction);

    /* �� */
    GPIO_InitStruction.GPIO_Mode=GPIO_Mode_IPD;                                   //��������
    GPIO_InitStruction.GPIO_Pin=GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_8;      //PB��5��6��7��8  R1��R2��R3��R4
    GPIO_InitStruction.GPIO_Speed=GPIO_Speed_50MHz;
    GPIO_Init(GPIOB,&GPIO_InitStruction);

}

/**************************************************************
��������: Value44Key(void)
��������: �ж�4X4���󰴼��Ƿ���
�������: ��


�� �� ֵ: ���󰴼���ֵ
��    ע: ��
**************************************************************/
int Value44Key(void)                                          //���������̵ķ���ֵ������ֵ��Ӧ��ع��ܣ�
{
    int KeyValue = 0;                                         //KeyValue����󷵻صİ�����ֵ
    GPIO_Write(GPIOB,((GPIOB->ODR & 0x0FFF )| 0xF000));       //����PB12 - PB15ȫ�������

    if((GPIOB->IDR & 0x01E0) == 0x0000)                       //������ PB5 - PB8 Ϊ0�����û�а������£�����ֵΪ-1
    {
        return -1;
    }
    else                                                     //�а�������
    {
        delay_ms(10);                                         //��ʱ10msȥ����
        if((GPIOB->IDR & 0x01E0) == 0x0000)                  //�����ʱ5ms�� PB5 - PB8 ��ȫΪ0�� ��ո��Ƕ���������
        {
            return -1;                                       //���Ի��Ƿ��� -1
        }
        else
        {
            GPIO_Write(GPIOB, (GPIOB->ODR & 0x0FFF )| 0x8000 );       //Ҫ�� PB12 - PB15 ��������Ƶ� 0001
            switch(GPIOB->IDR & 0x01E0)                               //��Ӧ�� PB5 - PB8 ��ֵ�����жϣ������ͬ�İ���ֵ
            {
            case 0x0100:
                KeyValue = 15;
                break;

            case 0x0080:
                KeyValue = 11;
                break;

            case 0x0040:
                KeyValue = 7;
                break;

            case 0x0020:
                KeyValue = 3;
                break;
            }

            GPIO_Write(GPIOB, (GPIOB->ODR & 0x0FFF )| 0x4000 );        //Ҫ�� PB12 - PB15 ��������Ƶ� 0010
            switch(GPIOB->IDR & 0x01E0)                                //��Ӧ�� PB5 - PB8 ��ֵ�����жϣ������ͬ�İ���ֵ
            {
            case 0x0100:
                KeyValue = 14;
                break;

            case 0x0080:
                KeyValue = 10;
                break;

            case 0x0040:
                KeyValue = 6;
                break;

            case 0x0020:
                KeyValue = 2;
                break;
            }

            GPIO_Write(GPIOB, (GPIOB->ODR & 0x0FFF )| 0x2000 );      //Ҫ�� PB12 - PB15 ��������Ƶ� 0100
            switch(GPIOB->IDR & 0x01E0)                              //��Ӧ�� PB5 - PB8 ��ֵ�����жϣ������ͬ�İ���ֵ
            {
            case 0x0100:
                KeyValue = 13;
                break;

            case 0x0080:
                KeyValue = 9;
                break;

            case 0x0040:
                KeyValue = 5;
                break;

            case 0x0020:
                KeyValue = 1;
                break;
            }

            GPIO_Write(GPIOB, (GPIOB->ODR & 0x0FFF )| 0x1000 );      //Ҫ�� PB12 - PB15 ��������Ƶ� 1000
            switch(GPIOB->IDR & 0x01E0)                              //��Ӧ�� PB5 - PB8 ��ֵ�����жϣ������ͬ�İ���ֵ
            {
            case 0x0100:
                KeyValue = 12;
                break;

            case 0x0080:
                KeyValue = 8;
                break;

            case 0x0040:
                KeyValue = 4;
                break;

            case 0x0020:
                KeyValue = 0;
                break;
            }

            while(((GPIOB->IDR & 0x01E0)==0x0000) && (relayms--))      //�������ּ��
            {
                delay_ms(1);
            }

            return KeyValue;
        }
    }
}





