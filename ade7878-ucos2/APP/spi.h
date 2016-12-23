#ifndef __SPI_H
#define __SPI_H
#include"stm32f10x.h"

#define SPI_FLAG_RXNE 	    SPI_I2S_FLAG_RXNE
#define SPI_FLAG_TXE 		SPI_I2S_FLAG_TXE

#define SPI_FLAG_OVR            SPI_I2S_FLAG_OVR
#define SPI_FLAG_BSY            SPI_I2S_FLAG_BSY

#define SPI_GetFlagStatus       SPI_I2S_GetFlagStatus
#define SPI_SendData            SPI_I2S_SendData 
#define SPI_ReceiveData 		SPI_I2S_ReceiveData

void SPI2_Init(void);
unsigned char SPI2_ReadWrite(unsigned char SPI_Send_byte);
//unsigned char SPI2_ReadByte(unsigned char SPI_Send_byte);
//void SPI2_WriteByte(unsigned char TxData);

#endif

