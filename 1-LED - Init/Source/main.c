/*********************************************************************************************
* �ļ���main.c
* ���ߣ�chennian 2017.11.02
* ˵����D1��D2��D3��D4����ʵ�����    
* ���ܣ�
* �޸ģ�

*********************************************************************************************/

/*********************************************************************************************
* ͷ�ļ�
*********************************************************************************************/
#include "stm32f4xx.h"
#include "delay.h"
#include "led.h"
#include "key.h"
/*********************************************************************************************
* ���ƣ�main()
* ���ܣ�LEDʵ���߼�����
* ��������
* ���أ���
* �޸ģ�
*********************************************************************************************/
char led_status = 0;
void check(){
    if(get_key_status() == K1_PREESED){                         //���K1������
      delay_count(60);
      turn_on(D1);
      while(get_key_status() == K1_PREESED);                  //�ȴ������ɿ�
          turn_off(D1);
          led_status = 0;
    }else if(get_key_status() == K2_PREESED){                         //���K2������
      delay_count(60);
      turn_on(D2);
      while(get_key_status() == K2_PREESED);                  //�ȴ������ɿ�
         turn_off(D2);
         led_status = 0;
    }else if(get_key_status() == K3_PREESED){                        
      delay_count(60);
      turn_on(D3);
      while(get_key_status() == K3_PREESED);                  //�ȴ������ɿ�
          turn_off(D3);
          led_status = 0;

    }else if(get_key_status() == K4_PREESED){                         //���K4������
      delay_count(60);
      turn_on(D4);
      while(get_key_status() == K4_PREESED);
         turn_off(D4);
         led_status = 0;
    }
 }
void main(void)
{
                                           //����һ����ʾLED״̬�ı���
  led_init();                            
  //��ʼ��LED���ƹܽ�
  key_init();
  //��ʼ���������ܽ�
  while(1){                                                     //ѭ����
    if(led_status == 0){    
      turn_on(D1);
      delay_count(5000);
      turn_off(D1);
      check();
      delay_count(5000);
      turn_on(D2);
      delay_count(5000);
      turn_off(D2);
      check();
      delay_count(5000);
      turn_on(D3);
      delay_count(5000);
      turn_off(D3);
      check();
      delay_count(5000);
      turn_on(D4);
      delay_count(5000);
      turn_off(D4);
      check();
                                     
    }
  }
}