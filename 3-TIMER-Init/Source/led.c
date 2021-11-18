/*********************************************************************************************
* �ļ�: led.c
* ���ߣ�liutong 2015.8.19
* ˵����LED��������
*       D1->PE0;D2->PE1;D3->PE2;D4->PE3;R->PB0;G->PB1;B->PB2
* �޸ģ�chennian 2017.11.02 �޸ĳ�ʼ������
*       chennian 2017.11.22 ����ע��
* ע�ͣ�
*********************************************************************************************/
#include "led.h"
/*********************************************************************************************
* ���ƣ�led_init
* ���ܣ���ʼ��LED��Ӧ��GPIO
* ��������
* ���أ���
* �޸ģ�
* ע�ͣ�
*********************************************************************************************/
void led_init(void)
{
  GPIO_InitTypeDef  GPIO_InitStructure;                    
  
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE | 
                         RCC_AHB1Periph_GPIOB , ENABLE);        //ʹ��GPIOʱ��
  
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 |
                                GPIO_Pin_2 | GPIO_Pin_3;        //ѡ������
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;                 //���ģʽ
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;                //�������
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;              //����ٶ�2MHz
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;              //��������
  GPIO_Init(GPIOE, &GPIO_InitStructure);                        //����������������GPIOE0��GPIOE1��GPIOE2��GPIOE3
  GPIO_SetBits(GPIOE, GPIO_Pin_0 | GPIO_Pin_1 |
                      GPIO_Pin_2 | GPIO_Pin_3);
  
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | 
                                GPIO_Pin_1 |
                                GPIO_Pin_2 ;                    //ѡ��0��1��2������
  GPIO_Init(GPIOB, &GPIO_InitStructure);                        //����������������GPIOB0��GPIOB1��GPIOB2  
  GPIO_SetBits(GPIOB, GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2);    //GPIOB0��GPIOB1��GPIOB2������Ϊ�ߵ�ƽ
}

/*********************************************************************************************
* ���ƣ�Turn_off
* ���ܣ������Ÿߵ�ƽ���ر�LED
* ������led
* ���أ���
* �޸ģ�
* ע�ͣ�
*********************************************************************************************/
void turn_off(unsigned char led){
  if(led & D1)                                                  //�ж�LEDѡ��
    GPIO_SetBits(GPIOE, GPIO_Pin_0);                            //PE0�����Ÿߵ�ƽ���ر�D1
  if(led & D2)
    GPIO_SetBits(GPIOE, GPIO_Pin_1);                            //PE1�����Ÿߵ�ƽ���ر�D2
  if(led & D3)
    GPIO_SetBits(GPIOE, GPIO_Pin_2);                            //PE2�����Ÿߵ�ƽ���ر�D3
  if(led & D4)
    GPIO_SetBits(GPIOE, GPIO_Pin_3);                            //PE3�����Ÿߵ�ƽ���ر�D4
  if(led & LEDR)
    GPIO_SetBits(GPIOB, GPIO_Pin_0);                            //PB0�����Ÿߵ�ƽ���ر�RGB�Ƶĺ��
  if(led & LEDG)
    GPIO_SetBits(GPIOB, GPIO_Pin_1);                            //PB1�����Ÿߵ�ƽ���ر�RGB�Ƶ��̵�
  if(led & LEDB)
    GPIO_SetBits(GPIOB, GPIO_Pin_2);                            //PB2�����Ÿߵ�ƽ���ر�RGB�Ƶ�����
}

/*********************************************************************************************
* ���ƣ�turn_on
* ���ܣ������ŵ͵�ƽ����LED
* ������led
* ���أ���
* �޸ģ�
* ע�ͣ�
*********************************************************************************************/
void turn_on(unsigned char led){
  if(led & D1)                                                  //�ж�LEDѡ��
    GPIO_ResetBits(GPIOE, GPIO_Pin_0);                          //PE0�����ŵ͵�ƽ����D1
  if(led & D2)
    GPIO_ResetBits(GPIOE, GPIO_Pin_1);                          //PE1�����ŵ͵�ƽ����D2
  if(led & D3)
    GPIO_ResetBits(GPIOE, GPIO_Pin_2);                          //PE2�����ŵ͵�ƽ����D3
  if(led & D4)
    GPIO_ResetBits(GPIOE, GPIO_Pin_3);                          //PE3�����ŵ͵�ƽ����D4
  if(led & LEDR)
    GPIO_ResetBits(GPIOB, GPIO_Pin_0);                          //PB0�����ŵ͵�ƽ����RGB�Ƶĺ��
  if(led & LEDG)
    GPIO_ResetBits(GPIOB, GPIO_Pin_1);                          //PB1�����ŵ͵�ƽ����RGB�Ƶ��̵�
  if(led & LEDB)
    GPIO_ResetBits(GPIOB, GPIO_Pin_2);                          //PB2�����ŵ͵�ƽ����RGB�Ƶ�����
}
/*********************************************************************************************
* ���ƣ�get_led_status
* ���ܣ���ȡLED״̬
* ������
* ���أ�led_status--bit0-bit3�ֱ��ʾ4·LED�Ƶ�״̬��bit4-bit6�ֱ��ʾRGB�Ƶ�״̬
* �޸ģ�
* ע�ͣ�
*********************************************************************************************/
unsigned char get_led_status(void){
  unsigned char led_status = 0;
  if(GPIO_ReadOutputDataBit(GPIOE, GPIO_Pin_0))                 //�ж�PE0���ŵ�ƽ
    led_status |= D1;                                           //�ߵ�ƽ��led_status bit0��1
  else
    led_status &= ~D1;                                          //�͵�ƽ��led_status bit0��0
  
  if(GPIO_ReadOutputDataBit(GPIOE, GPIO_Pin_1))                 //�ж�PE1���ŵ�ƽ
    led_status |= D2;                                           //�ߵ�ƽ��led_status bit1��1
  else
    led_status &= ~D2;                                          //�͵�ƽ��led_status bit1��0
  
  if(GPIO_ReadOutputDataBit(GPIOE, GPIO_Pin_2))                 //�ж�PE2���ŵ�ƽ
    led_status |= D3;                                           //�ߵ�ƽ��led_status bit2��1
  else
    led_status &= ~D3;                                          //�͵�ƽ��led_status bit2��0
  
  if(GPIO_ReadOutputDataBit(GPIOE, GPIO_Pin_3))                 //�ж�PE3���ŵ�ƽ
    led_status |= D4;                                           //�ߵ�ƽ��led_status bit3��1
  else
    led_status &= ~D4;                                          //�͵�ƽ��led_status bit3��0
  
  if(GPIO_ReadOutputDataBit(GPIOB, GPIO_Pin_0))                 //�ж�PB0���ŵ�ƽ
    led_status |= LEDR;                                         //�ߵ�ƽ��led_status bit4��1
  else
    led_status &= ~LEDR;                                        //�͵�ƽ��led_status bit4��0
  
  if(GPIO_ReadOutputDataBit(GPIOB, GPIO_Pin_1))                 //�ж�PB1���ŵ�ƽ
    led_status |= LEDG;                                         //�ߵ�ƽ��led_status bit5��1
  else
    led_status &= ~LEDG;                                        //�͵�ƽ��led_status bit5��0
  
  if(GPIO_ReadOutputDataBit(GPIOB, GPIO_Pin_2))                 //�ж�PB2���ŵ�ƽ
    led_status |= LEDB;                                         //�ߵ�ƽ��led_status bit6��1
  else
    led_status &= ~LEDB;                                        //�͵�ƽ��led_status bit6��0
  return led_status;                                            //����led_status
}
