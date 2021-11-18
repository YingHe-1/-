/*********************************************************************************************
* �ļ���main.c
* ���ߣ�chennain 2017.11.02
* ˵����    
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
#include "timer.h"
char led_status;                                            //����һ����ʾLED��״̬�ı���
char led_status2;
char led_status3;
/*********************************************************************************************
* ���ƣ�main()
* ���ܣ�LED����ʵ���߼�����
* ��������
* ���أ���
* �޸ģ�
*********************************************************************************************/

int count = 0;

void key(){
  if(get_key_status() == K3_PREESED){                           //���K3������
    delay_count(500);                                           //��ʱ����
    if(get_key_status() == K3_PREESED){                         //ȷ��K3������
      while(get_key_status() == K3_PREESED);                    //�ȴ������ɿ�
      //led_status = !led_status;                                 //��תled״̬��־
      count++;
    }
  }
}

void main(void)
{
  led_status=-1;
  led_init();                            //��ʼ��LED���ƹܽ�
  key_init();                           //��ʼ���������ܽ�
  timer3_init(2500-1, 16800-1);
  timer4_init(5000-1, 16800-1);
//��չ1
  while(1){
    key();
    if(count==0){
      TIM_Cmd(TIM4, ENABLE);
        turn_off(D1);
        turn_off(D2);
      if(led_status3 == 0){                                        //LED��Ϊ״̬0
        turn_on(D3);                                              //D3��
        turn_off(D4);                                             //D4��
      }
      else{                                                       //LED��Ϊ״̬1
        turn_off(D3);                                             //D3��
        turn_on(D4);                                              //D4��
      }
      TIM_Cmd(TIM4, DISABLE);
    }
    else if(count==1){
          TIM_Cmd(TIM3, ENABLE);                                  
          turn_off(D1);
          turn_off(D2); 
          turn_off(D3);
          turn_off(D4);
      if(led_status == 0){
          turn_on(D1);        
      }  
      else if(led_status == 1){
          turn_on(D2); 
      }
      else if(led_status == 2){
          turn_on(D3);
      }
      else if(led_status == 3){
          turn_on(D4);
      }
      TIM_Cmd(TIM3, DISABLE);
    } 
    else if(count==2){ 
          TIM_Cmd(TIM3, ENABLE);                                  
          if(led_status2 == 0){
            turn_on(D1);
            turn_on(D2); 
            turn_on(D3);
            turn_on(D4);
          }
          else if(led_status2 == 1){
            turn_off(D1);
            turn_off(D2); 
            turn_off(D3);
            turn_off(D4);
          }
          TIM_Cmd(TIM3, DISABLE);
    }
    else if(count==3){
      count=0;
    }
  }
  
}

