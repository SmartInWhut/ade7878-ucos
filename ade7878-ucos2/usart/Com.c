#include "includes.h"


void USART_Config(void){
  GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;

	/* 第1步：打开GPIO和USART部件的时钟 */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_AFIO, ENABLE);
    RCC_APB2PeriphClockCmd( RCC_APB2Periph_USART1 , ENABLE);	 //使能串口2时钟

	/* 第2步：将USART Tx的GPIO配置为推挽复用模式 */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;	         		 //USART2 TX
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;    		 //复用推挽输出
	GPIO_Init(GPIOA, &GPIO_InitStructure);		    		 //A端口 
	

	/* 第3步：将USART Rx的GPIO配置为浮空输入模式
		由于CPU复位后，GPIO缺省都是浮空输入模式，因此下面这个步骤不是必须的
		但是，我还是建议加上便于阅读，并且防止其它地方修改了这个口线的设置参数
	*/
	  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;	             	 //USART2 RX
	  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;   	 //复用开漏输入
	  GPIO_Init(GPIOA, &GPIO_InitStructure);		         	 //A端口 



	/* 第4步：配置USART参数
	    - 波特率   = 115200 baud
	    - 数据长度 = 8 Bits
	    - 1个停止位
	    - 无校验
	    - 禁止硬件流控(即禁止RTS和CTS)
	    - 使能接收和发送
	*/
	USART_InitStructure.USART_BaudRate = 115200;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	USART_Init(USART1, &USART_InitStructure);

	/* 第5步：使能 USART， 配置完毕 */
	USART_Cmd(USART1, ENABLE);	

	USART_ClearFlag(USART1, USART_FLAG_TXE);     /* 清发送完成标志，Transmission Complete flag */
}
