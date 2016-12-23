#include "includes.h"


void USART_Config(void){
  GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;

	/* ��1������GPIO��USART������ʱ�� */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_AFIO, ENABLE);
    RCC_APB2PeriphClockCmd( RCC_APB2Periph_USART1 , ENABLE);	 //ʹ�ܴ���2ʱ��

	/* ��2������USART Tx��GPIO����Ϊ���츴��ģʽ */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;	         		 //USART2 TX
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;    		 //�����������
	GPIO_Init(GPIOA, &GPIO_InitStructure);		    		 //A�˿� 
	

	/* ��3������USART Rx��GPIO����Ϊ��������ģʽ
		����CPU��λ��GPIOȱʡ���Ǹ�������ģʽ���������������費�Ǳ����
		���ǣ��һ��ǽ�����ϱ����Ķ������ҷ�ֹ�����ط��޸���������ߵ����ò���
	*/
	  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;	             	 //USART2 RX
	  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;   	 //���ÿ�©����
	  GPIO_Init(GPIOA, &GPIO_InitStructure);		         	 //A�˿� 



	/* ��4��������USART����
	    - ������   = 115200 baud
	    - ���ݳ��� = 8 Bits
	    - 1��ֹͣλ
	    - ��У��
	    - ��ֹӲ������(����ֹRTS��CTS)
	    - ʹ�ܽ��պͷ���
	*/
	USART_InitStructure.USART_BaudRate = 115200;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	USART_Init(USART1, &USART_InitStructure);

	/* ��5����ʹ�� USART�� ������� */
	USART_Cmd(USART1, ENABLE);	

	USART_ClearFlag(USART1, USART_FLAG_TXE);     /* �巢����ɱ�־��Transmission Complete flag */
}
