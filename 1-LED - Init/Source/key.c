/*********************************************************************************************
* �ļ���key.c
* ���ߣ�chennian 2017.11.02
* ˵����K1 ��Ӧ���� PB12
*       K2 ��Ӧ�ܽ� PB13
*       K3 ��Ӧ���� PB14
*       K4 ��Ӧ�ܽ� PB15
* ���ܣ�������������
* �޸ģ�zhoucj   2017.12.18 ����ע��
*********************************************************************************************/
/*********************************************************************************************
* ͷ�ļ�
*********************************************************************************************/
#include "key.h"

/*********************************************************************************************
* ���ƣ�key_init
* ���ܣ������ܽų�ʼ��
* ��������
* ���أ���
* �޸ģ���
*********************************************************************************************/
void key_init(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;                          //����һ��GPIO_InitTypeDef���͵Ľṹ��
  RCC_AHB1PeriphClockCmd( K1_CLK | K2_CLK
                         |K3_CLK | K4_CLK, ENABLE);             //����KEY��ص�GPIO����ʱ��
  
  GPIO_InitStructure.GPIO_Pin = K1_PIN | K2_PIN |
                                K3_PIN | K4_PIN;                //ѡ��Ҫ���Ƶ�GPIO����
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;                //�������ŵ��������Ϊ�������
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;                  //��������ģʽΪ����ģʽ
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;                  //��������Ϊ����ģʽ
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;              //������������Ϊ2MHz
  
  GPIO_Init(K1_PORT, &GPIO_InitStructure);                      //��ʼ��GPIOB����
  GPIO_Init(K2_PORT, &GPIO_InitStructure);                      //��ʼ��GPIOB����
  GPIO_Init(K3_PORT, &GPIO_InitStructure);                      //��ʼ��GPIOB����
  GPIO_Init(K4_PORT, &GPIO_InitStructure);                      //��ʼ��GPIOB����
}

/*********************************************************************************************
* ���ƣ�get_key_status
* ���ܣ������ܽų�ʼ��
* ��������
* ���أ�key_status
* �޸ģ�
*********************************************************************************************/
char get_key_status(void)
{
  char key_status = 0;
  if(GPIO_ReadInputDataBit(K1_PORT,K1_PIN) == 0)                //�ж�PB12���ŵ�ƽ״̬
    key_status |= K1_PREESED;                                   //�͵�ƽkey_status bit0λ��1
  if(GPIO_ReadInputDataBit(K2_PORT,K2_PIN) == 0)                //�ж�PB13���ŵ�ƽ״̬
    key_status |= K2_PREESED;                                   //�͵�ƽkey_status bit1λ��1
  if(GPIO_ReadInputDataBit(K3_PORT,K3_PIN) == 0)                //�ж�PB14���ŵ�ƽ״̬
    key_status |= K3_PREESED;                                   //�͵�ƽkey_status bit2λ��1
  if(GPIO_ReadInputDataBit(K4_PORT,K4_PIN) == 0)                //�ж�PB15���ŵ�ƽ״̬
    key_status |= K4_PREESED;                                   //�͵�ƽkey_status bit3λ��1
  return key_status;
}
