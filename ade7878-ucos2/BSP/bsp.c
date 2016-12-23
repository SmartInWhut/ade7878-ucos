#include "..\App\includes.h"
#include "globals.h"
/*
*********************************************************************************************************

*/

/*******************************************************************************
* Function Name  : RCC_Configuration
* Description    : Configures the different system clocks.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/

////////////////////////////////////////////////////////
void RCC_Configuration(void)
{	
	SystemInit();
}

extern unsigned char CIRMSReg[DataBufferSize*4],ICWVReg[4],VCWVReg[4], CWATTHRReg[4],
                     CVRMSReg[DataBufferSize*4], CWATTReg[4],Status_1[4],Status_0[4],
					 VPEAKReg[DataBufferSize*4],IPEAKReg[DataBufferSize*4],MASK0_data[4];
void BSP_Init(void)
{
	
	unsigned char CONFIG2dat[1]={0x00},MMODEdat[1]={0x04},GAINdat[2];
	
  /* System Clocks Configuration --72M*/
	RCC_Configuration();
   
	USART_Config();		  //串口1初始化 
   
	ADE7878_init();

	OSTimeDlyHMSM(0,0,0,5);
	Read_ADE7878_SPI(CONFIG2,1,CONFIG2dat);
	Read_ADE7878_SPI(MMODE,1,MMODEdat);
	Read_ADE7878_SPI(GAIN,2,GAINdat);
	Read_ADE7878_SPI(STATUS1,4,Status_1);
	Read_ADE7878_SPI(MASK0,4,MASK0_data);
	Read_ADE7878_SPI(STATUS1,4,Status_0);
  	OSTimeDlyHMSM(0,0,0,500);

	EXTI_Config();
	TIM3_Init();
}






////SYSTICK 配置， 10ms一次systick中断，产生ucos 调度节拍， 1KHz
void  OS_CPU_SysTickInit(void)
{
    RCC_ClocksTypeDef  rcc_clocks;
    INT32U         cnts;


    RCC_GetClocksFreq(&rcc_clocks);

    cnts = (INT32U)rcc_clocks.HCLK_Frequency/OS_TICKS_PER_SEC;

	SysTick_Config(cnts);

  
}
/******************* (C) COPYRIGHT 2008 STMicroelectronics *****END OF FILE****/

