#include "includes.h"

void SPI2_Init(void)
{
  SPI_InitTypeDef SPI_InitStructure;
  GPIO_InitTypeDef GPIO_InitStructure;

  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB|RCC_APB2Periph_AFIO, ENABLE);
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI2, ENABLE);

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13|GPIO_Pin_15;  //sck mosi
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;         //推挽复用
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
  SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;  //双线输入输出全双工模式
  SPI_InitStructure.SPI_Mode = SPI_Mode_Master;        //设置为SPI的主机模式
  SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;        //SPI数据大小：发送8位帧数据结构
  SPI_InitStructure.SPI_CPOL = SPI_CPOL_High;        //设备空闲状态时同步时钟SCK的状态，High表示高电平，Low表示低电平
  SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge;    //时钟相位，1表示在同步时钟SCK的奇数沿边采样，2表示偶数沿边采样
  SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;        //NSS由软件控件片选
  SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_16;//时钟的预分频值
  SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;    //MSB高位在前
  SPI_InitStructure.SPI_CRCPolynomial = 7;                //CRC较验和的多项式
  SPI_Init(SPI2, &SPI_InitStructure);                          //初始化SPI2的配置项
  SPI_Cmd(SPI2, ENABLE);
  
  SPI2_ReadWrite(0xff);                                      //使能SPI2   

}


unsigned char SPI2_ReadWrite(unsigned char SPI_Send_byte)
{
   while(SPI_I2S_GetFlagStatus(SPI2,SPI_FLAG_TXE)==RESET);	 //等待发送缓冲器为空
   SPI_I2S_SendData(SPI2,SPI_Send_byte);
   while(SPI_I2S_GetFlagStatus(SPI2,SPI_I2S_FLAG_RXNE)==RESET);	  //等待接收缓冲器有数据进来
   return SPI_I2S_ReceiveData(SPI2);
}


