#include "includes.h"

void SPI2_Init(void)
{
  SPI_InitTypeDef SPI_InitStructure;
  GPIO_InitTypeDef GPIO_InitStructure;

  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB|RCC_APB2Periph_AFIO, ENABLE);
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI2, ENABLE);

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13|GPIO_Pin_15;  //sck mosi
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;         //���츴��
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;   
  GPIO_Init(GPIOB,&GPIO_InitStructure);

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14;             //miso
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;   
//  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;   
  GPIO_Init(GPIOB,&GPIO_InitStructure);

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;              //cs
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;   
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;   
  GPIO_Init(GPIOB,&GPIO_InitStructure);

  SPI_Cmd(SPI2, DISABLE);  
  SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;  //˫���������ȫ˫��ģʽ
  SPI_InitStructure.SPI_Mode = SPI_Mode_Master;        //����ΪSPI������ģʽ
  SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;        //SPI���ݴ�С������8λ֡���ݽṹ
  SPI_InitStructure.SPI_CPOL = SPI_CPOL_High;        //�豸����״̬ʱͬ��ʱ��SCK��״̬��High��ʾ�ߵ�ƽ��Low��ʾ�͵�ƽ
  SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge;    //ʱ����λ��1��ʾ��ͬ��ʱ��SCK�������ر߲�����2��ʾż���ر߲���
  SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;        //NSS������ؼ�Ƭѡ
  SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_16;//ʱ�ӵ�Ԥ��Ƶֵ
  SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;    //MSB��λ��ǰ
  SPI_InitStructure.SPI_CRCPolynomial = 7;                //CRC����͵Ķ���ʽ
  SPI_Init(SPI2, &SPI_InitStructure);                          //��ʼ��SPI2��������
  SPI_Cmd(SPI2, ENABLE);
  
  SPI2_ReadWrite(0xff);                                      //ʹ��SPI2   

}


unsigned char SPI2_ReadWrite(unsigned char SPI_Send_byte)
{
   while(SPI_I2S_GetFlagStatus(SPI2,SPI_FLAG_TXE)==RESET);	 //�ȴ����ͻ�����Ϊ��
   SPI_I2S_SendData(SPI2,SPI_Send_byte);
   while(SPI_I2S_GetFlagStatus(SPI2,SPI_I2S_FLAG_RXNE)==RESET);	  //�ȴ����ջ����������ݽ���
   return SPI_I2S_ReceiveData(SPI2);
}


