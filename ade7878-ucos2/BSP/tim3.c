/******************
           使用基本定时器TIM3作为计时器
          **********************************************************/
#include "includes.h"
/*
 * 函数名：TIM6_Init()
 * 输入  ：无
 * 输出  ：无
 * 调用  ：内部调用
 */

void TIM3_Init(void)
{
    
	  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	  NVIC_InitTypeDef NVIC_InitStructure;
	 
	  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	  NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;
	  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1; /*它的抢占优先级可以尽量设置低点*/
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
	  TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE); //溢出为中断源
	  TIM_ARRPreloadConfig(TIM3, ENABLE);			 // 使能TIM3重载寄存器ARR

	  /* TIM6 enable counter */
	   TIM_Cmd(TIM3, ENABLE);                   //使能定时器3	
}




