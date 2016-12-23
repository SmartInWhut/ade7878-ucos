/******************
           ʹ�û�����ʱ��TIM3��Ϊ��ʱ��
          **********************************************************/
#include "includes.h"
/*
 * ��������TIM6_Init()
 * ����  ����
 * ���  ����
 * ����  ���ڲ�����
 */

void TIM3_Init(void)
{
    
	  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	  NVIC_InitTypeDef NVIC_InitStructure;
	 
	  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	  NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;
	  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1; /*������ռ���ȼ����Ծ������õ͵�*/
	  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
	  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	  NVIC_Init(&NVIC_InitStructure);
  
	  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
	  TIM_TimeBaseStructure.TIM_Period = 80-1;
	  TIM_TimeBaseStructure.TIM_Prescaler = 900-1;
	  TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;	
	  TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);

	  TIM_ClearITPendingBit(TIM3, TIM_IT_Update); 
	  TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE); //���Ϊ�ж�Դ
	  TIM_ARRPreloadConfig(TIM3, ENABLE);			 // ʹ��TIM3���ؼĴ���ARR

	  /* TIM6 enable counter */
	   TIM_Cmd(TIM3, ENABLE);                   //ʹ�ܶ�ʱ��3	
}




