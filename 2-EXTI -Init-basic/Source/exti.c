/*********************************************************************************************
* �ļ���exti.c
* ˵����
* ���ܣ��ⲿ�ж���������
* �޸ģ�������������
        zhoucj   2017.12.18 �޸�ע��
*********************************************************************************************/

/*********************************************************************************************
* ͷ�ļ�
*********************************************************************************************/
#include "exti.h"
#include "key.h"
#include "delay.h"
extern char led_status;  
/*********************************************************************************************
* ���ƣ�exti_init
* ���ܣ��ⲿ�жϳ�ʼ��
* ��������
* ���أ���
* �޸ģ���
*********************************************************************************************/
void exti_init(void)
{
  key_init();                                                   //�������ų�ʼ��
  NVIC_InitTypeDef   NVIC_InitStructure;
  EXTI_InitTypeDef   EXTI_InitStructure;
  
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);        //ʹ��SYSCFGʱ��
  SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOB, EXTI_PinSource14); //PB14 ���ӵ��ж���14
  SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOB, EXTI_PinSource15); //PB15 ���ӵ��ж���15
  
  EXTI_InitStructure.EXTI_Line = EXTI_Line14 | EXTI_Line15;     //LINE14��LINE15
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;           //�ж��¼�
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;       //�½��ش��� 
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;                     //ʹ��LINE14��LINE15
  EXTI_Init(&EXTI_InitStructure);                               //��������������
  
  NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;          //�ⲿ�ж�15-10
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;     //��ռ���ȼ�0
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;            //�����ȼ�1
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;               //ʹ���ⲿ�ж�ͨ��
  NVIC_Init(&NVIC_InitStructure);                               //���������ó�ʼ��
  
}
/*********************************************************************************************
* ���ƣ�EXTI15_10_IRQHandler
* ���ܣ��ⲿ�ж�15-10�жϴ�����
* ��������
* ���أ���
* �޸ģ�
* ע�ͣ�
*********************************************************************************************/
void EXTI15_10_IRQHandler(void)
{
  if(get_key_status() == K3_PREESED){                           //���K3������
    delay_count(500);                                           //��ʱ����
    if(get_key_status() == K3_PREESED){                         //ȷ��K3������
      while(get_key_status() == K3_PREESED);                    //�ȴ������ɿ�
      led_status = !led_status;                                 //��תled״̬��־
    }
  }
  if(EXTI_GetITStatus(EXTI_Line14)!=RESET)
    EXTI_ClearITPendingBit(EXTI_Line14);                        //���LINE14�ϵ��жϱ�־λ
  if(EXTI_GetITStatus(EXTI_Line15)!=RESET)
    EXTI_ClearITPendingBit(EXTI_Line15);                        //���LINE15�ϵ��жϱ�־λ
}
