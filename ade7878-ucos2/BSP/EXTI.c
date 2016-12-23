/******************
           使用硬件中断检测线周期  YANKE
          **********************************************************/
#include "includes.h"

void EXTI_Config(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
  EXTI_InitTypeDef EXTI_InitStructure;
  NVIC_InitTypeDef NVIC_InitStructure;

//  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC | RCC_APB2Periph_AFIO, ENABLE);
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD | RCC_APB2Periph_AFIO, ENABLE);
  
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
  NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;
//  NVIC_InitStructure.NVIC_IRQChannel = EXTI2_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1; /*它的抢占优先级可以尽量设置低点*/
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;	         		 //USART2 TX
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;    		 //上拉输入

  GPIO_Init(GPIOD, &GPIO_InitStructure);
  GPIO_EXTILineConfig(GPIO_PortSourceGPIOD,GPIO_PinSource12);



  EXTI_InitStructure.EXTI_Line = EXTI_Line12;
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt ;
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling ;
  EXTI_InitStructure.EXTI_LineCmd = ENABLE ;
  EXTI_Init(&EXTI_InitStructure) ;

}
