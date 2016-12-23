#include "includes.h"

void ADE7878_GPIOCONFIG(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD,ENABLE);

  	/* Configure SPI2 pins: RESET, PM0,and PM1 */		 
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOD, &GPIO_InitStructure); 
//
//  	/* Configure SPI2 pins: NSS, SCK,and MOSI */		 
//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13 | GPIO_Pin_15;
//	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
//	GPIO_Init(GPIOB, &GPIO_InitStructure);
//	/*NSS   */
//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
//	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
//	GPIO_Init(GPIOB, &GPIO_InitStructure);
//	
//	/* MISO */
//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14;
//	GPIO_InitStructure.GPIO_Mode =  GPIO_Mode_AF_PP;   
//	GPIO_Init(GPIOB, &GPIO_InitStructure);
}

void ade7878_delay (u32 nCount)
{
	volatile int i;	 	
	for (i=0;i<nCount*100;i++);
}

void ADE7878_PSM0_Enable(void)
{
	ADE_RESET_0;
	ade7878_delay(20);
	ADE_RESET_1;
	ade7878_delay(5);
	ADE_PM0_1;
	ade7878_delay(5); 																				
	ADE_PM1_0;
	ade7878_delay(5);

}



//void ADE7878_PSM0_Enable(void)
//{
//  ADE_RESET_0;
//  delay_ms(15);
//  ADE_RESET_1;
//  delay_ms(15);
//  ADE_PM0_1;
//  delay_ms(1);
//  ADE_PM1_0;
//}

void Write_ADE7878_SPI(unsigned int ADE_Addr,unsigned char Nr_Bytes,unsigned char *pReg_Data)
{
  unsigned char i;
  unsigned char MS_Addr;
  unsigned char LS_Addr;
  LS_Addr=(unsigned char) ADE_Addr;
  MS_Addr=(unsigned char) (ADE_Addr >> 8);
  ADE_CS_0;
//  delay_us(1);
  SPI2_ReadWrite(0x00);       //0x00表示接下来要对所发送地址对应的寄存器进行写操作
  SPI2_ReadWrite(MS_Addr);    
  SPI2_ReadWrite(LS_Addr);
//  pReg_Data=pReg_Data+(Nr_Bytes-1);
  for(i=0; i<Nr_Bytes; i++)
  {
  	SPI2_ReadWrite(*pReg_Data);
	pReg_Data++;
  }
//  delay_us(1);
  ADE_CS_1;
}

void Read_ADE7878_SPI(unsigned int ADE_Addr, unsigned char Nr_Bytes,unsigned char *pReg_Data)
{
  unsigned char i;
  unsigned char MS_Addr;
  unsigned char LS_Addr;
  LS_Addr=(unsigned char) ADE_Addr;
  MS_Addr=(unsigned char) (ADE_Addr >> 8);
  ADE_CS_0;
  SPI2_ReadWrite(0x01);	     //	0x01表示接下来要对所发送地址对应的寄存器进行读操作
  SPI2_ReadWrite(MS_Addr);
  SPI2_ReadWrite(LS_Addr);
//  pReg_Data=pReg_Data+(Nr_Bytes-1);
  for(i=0; i<Nr_Bytes; i++)
  {
  	//*pReg_Data=SPI2_ReadWrite(0x11);
	*pReg_Data=SPI2_ReadWrite(0xff);
  	pReg_Data++;
  }
  ADE_CS_1;
}

//void ADE7878_SPI_Enable(void)
//{
//  unsigned char CONFIG2Reg[1]={0x02};
//  ADE_CS_1;
//        delay_ms(1);
//  ADE_CS_0;
//        delay_ms(1);
//  ADE_CS_1;
//        delay_ms(1);
//  ADE_CS_0;
//        delay_ms(1);
//  ADE_CS_1;
//        delay_ms(1);
//  ADE_CS_0;
//        delay_ms(1);
//  ADE_CS_1;
//  Write_ADE7878_SPI(CONFIG2,1,CONFIG2Reg);
//}

void ADE7878_SPI_Enable(void)
{
  unsigned char CONFIG2Reg[1] = {0x02};
	ADE_CS_1;
		ade7878_delay(5);
	ADE_CS_0;
		ade7878_delay(5);
	ADE_CS_1;
		ade7878_delay(5);
	ADE_CS_0;
		ade7878_delay(5);
	ADE_CS_1;
		ade7878_delay(5);
	ADE_CS_0;
		ade7878_delay(5);
	ADE_CS_1;
   //Write_ADE7878_SPI(CONFIG2,1,CONFIG2Reg); //选取的通信方式（spi）维持不变
	Write_ADE7878_SPI(CONFIG2,1, CONFIG2Reg); //对CONFIG2寄存器执行任意写操作选取通信方式（spi）维持不变
}

void ADE7878_BASICCONFIG(void)
{
    unsigned char ACCMODE_cof[1]={0x00};

    unsigned char LCYCMODE_cof[1]={0x21};	//C相计入线周期过零计数，WATT置于线周期累计模式
//  unsigned char LCYCMODE_cof[1]={0x49};	//YK修改 2016.4.5
//  unsigned char LCYCMODE_cof[1]={0x09};	//A相计入线周期过零计数，WATT置于线周期累计模式
   
    unsigned char MMODE_cof[1]={0x12};
//  unsigned char MMODE_cof[1]={0x1c};
//	unsigned char MMODE_cof[1]={0x04};
    
	unsigned char RUN_cof[2]={0x00,0x01};

//  u8 LINECYC_cof[2]={0x00,0x64};   //100个斑驳周期
//	u8 LINECYC_cof[2]={0x03,0xe8};	 //1000个斑驳周期
//	u8 LINECYC_cof[2]={0x01,0x90};	 //400个斑驳周期
	u8 LINECYC_cof[2]={0x75,0x30};	 //30000个斑驳周期

//   u8 CFMODE_cof[2]={0x10,0x00};
     u8 CFMODE_cof[2]={0x08,0xc8};	 //YK修改 2016.4.5 CF1总有功 CF2总无功 CF3禁能
//   u8 CFMODE_cof[2]={0x0e,0x88};		 //YK修改 2016.4.6 CF1/CF2/CF3禁能

//   u8 CF1DEN_cof[2]={0x3D,0x09};
     u8 CF1DEN_cof[2]={0x00,0x0a};	 //YK修改 2016.4.5 

//   u8 APNOLOAD_cof[4]={0x00,0x00,0x00,0x00};
     u8 APNOLOAD_cof[4]={0x00,0x02,0x20,0x60};	 //YK修改 2016.4.5 
//   u8 APNOLOAD_cof[3]={0x00,0x39,0x1c};	 //YK修改 2016.4.5
 
     unsigned char GAIN_cof[2] = {0x00,0x00};// 增益为1，不放大
     unsigned char CONFIG_cof[2]={0x00,0x00};

//   unsigned char Compmode_cof[2]={0x00,0x01};
     unsigned char Compmode_cof[2]={0x00,0x04};
  
     unsigned char HPFDIS_cof[4]={0x00,0x00,0x00,0x00};
     unsigned char MASK_cof[8]={0x00,0x00,0x00,0x20,0x00,0x00,0x00,0x00};

//   u8 WTHR_cof[8]={0X00,0X00,0XB6,0x64,0x00,0x00,0x00,0x00};
//   u8 WTHR_cof[8]={0X00,0Xe0,0X70,0x4c,0x00,0x00,0x00,0x02};//YK修改 2016.4.5 0.01WH/LSB
     u8 WTHR_cof[8]={0x00,0xce,0x23,0x7b,0x00,0x00,0x00,0x04};//YK修改 2016.4.5 0.01WH/LSB	2016.7.31
  
  unsigned char RAM[2] ={0xAD,0X00};	 //取消RAM写保护
  Write_ADE7878_SPI(0xE7FE,1,RAM);	//这个地址是哪里来的
  Write_ADE7878_SPI(0xE7E3,1,RAM+1);
  											
  Write_ADE7878_SPI(GAIN,2,GAIN_cof);	   //config the  Gain of the PGA , 信号不增大

  Write_ADE7878_SPI(CONFIG,2,CONFIG_cof);	   //禁用积分器，设置电压电流相序对应等
  Write_ADE7878_SPI(ACCMODE,1,ACCMODE_cof);		//检测相序及功率累计相关知识
  Write_ADE7878_SPI(COMPMODE,2,Compmode_cof);	  //测角度，CF,视在功率等的设置
  Write_ADE7878_SPI(MMODE,1,MMODE_cof);			 //线周期以C相为基准以及开启峰值检测

  Write_ADE7878_SPI(LCYCMODE,1,LCYCMODE_cof);	//线周期累计模式，正常还是线周期
  Write_ADE7878_SPI(LINECYC,2,LINECYC_cof);	//线周期累计模式计数
//  Write_ADE7878_SPI(PEAKCYC,1,MMODE_cof);	//峰值检测半波周期数
  Write_ADE7878_SPI(PEAKCYC,1,LINECYC_cof);

  Write_ADE7878_SPI(MASK0,4,MASK_cof);
  Write_ADE7878_SPI(MASK1,4,MASK_cof+4);

  Write_ADE7878_SPI(WTHR0,4,WTHR_cof);	  //PMAX = 33,516,139	  0.01WH/LSB	 
  Write_ADE7878_SPI(WTHR1,4,WTHR_cof+4);
  Write_ADE7878_SPI(VATHR0,4,WTHR_cof);	  //PMAX = 33,516,139
  Write_ADE7878_SPI(VATHR1,4,WTHR_cof+4);
  Write_ADE7878_SPI(VARTHR0,4,WTHR_cof);	  //PMAX = 33,516,139
  Write_ADE7878_SPI(VARTHR1,4,WTHR_cof+4);
  Write_ADE7878_SPI(APNOLOAD,4,APNOLOAD_cof);
  Write_ADE7878_SPI(VANOLOAD,4,APNOLOAD_cof);
  Write_ADE7878_SPI(VARNOLOAD,4,APNOLOAD_cof);
  Write_ADE7878_SPI(CFMODE,2,CFMODE_cof);
  Write_ADE7878_SPI(CF1DEN,2,CF1DEN_cof);
  Write_ADE7878_SPI(CF2DEN,2,CF1DEN_cof);
  Write_ADE7878_SPI(CF3DEN,2,CF1DEN_cof);
  Write_ADE7878_SPI(CFCYC,1,RUN_cof+1);

  Write_ADE7878_SPI(HPFDIS,4,HPFDIS_cof);	   //enabled high-pass filters	
  Write_ADE7878_SPI(HPFDIS,4,HPFDIS_cof);	   //enabled high-pass filters	
  Write_ADE7878_SPI(HPFDIS,4,HPFDIS_cof);	   //enabled high-pass filters	
  Write_ADE7878_SPI(RUN,2,RUN_cof);        //启动DSP
}

void ADE7878_CORRECTCONFIG(void)
{  
// 电流校准
//    unsigned char CorrectReg_CIGAIN[4]={0x00,0x03,0x91,0x92};//YK修改 2016.3.22
//	unsigned char CorrectReg_CIGAIN[4]={0x00,0x17,0x81,0x65};//YK修改 2016.5.29
	unsigned char CorrectReg_CIGAIN[4]={0x00,0x03,0xa7,0x32};//YK修改 2016.6.15

//	unsigned char CorrectReg_CVGAIN[4]={0x00,0x06,0x56,0xac};//YK修改 2016.6.17
//	unsigned char CorrectReg_CVGAIN[4]={0x00,0x04,0x28,0x10};//YK修改 2016.6.17
//	unsigned char CorrectReg_CVGAIN[4]={0x00,0x05,0xeb,0xbb};//YK修改 2016.8.4 2号板子
//	unsigned char CorrectReg_CVGAIN[4]={0x00,0x08,0x6b,0xb6};//YK修改 2016.8.4 1号板子
//	unsigned char CorrectReg_CVGAIN[4]={0x00,0x05,0x5c,0x86};//YK修改 2016.8.4 3号板子
//  unsigned char CorrectReg_CVGAIN[4]={0x00,0x05,0x68,0x32};//YK修改 2016.8.4 5号板子
//	unsigned char CorrectReg_CVGAIN[4]={0x00,0x07,0x85,0xa2};//YK修改 2016.8.4 6号板子
//  unsigned char CorrectReg_CVGAIN[4]={0x00,0x04,0xe7,0x62};//YK修改 2016.8.4 7号板子
	unsigned char CorrectReg_CVGAIN[4]={0x00,0x05,0xb5,0x2d};//YK修改 2016.8.4 4号板子
//	unsigned char CorrectReg_CVGAIN[4]={0x00,0x04,0xd5,0x12};//YK修改 2016.8.4 8号板子

	unsigned char CorrectReg_CWGAIN[4]={0xff,0xff,0x29,0xb2};//YK修改 2016.6.17
//	unsigned char CorrectReg_APHCAL[2]={0x01,0x7f};//YK修改 2016.4.13
//	unsigned char CorrectReg_CPHCAL[2]={0x00,0xbf};//YK修改 2016.4.13
    Write_ADE7878_SPI(CIGAIN,4,CorrectReg_CIGAIN);	   //校准电流有效值
	Write_ADE7878_SPI(CVGAIN,4,CorrectReg_CVGAIN);	   //校准电压有效值
	Write_ADE7878_SPI(CWGAIN,4, CorrectReg_CWGAIN);	  //校准有功功率值
 // Write_ADE7878_SPI(AVGAIN,4,CorrectReg_cof);	
//  Write_ADE7878_SPI(BIGAIN,4,CorrectReg_cof);
//  Write_ADE7878_SPI(BVGAIN,4,CorrectReg_cof);	
//  Write_ADE7878_SPI(CIGAIN,4,CorrectReg_cof);	
//  Write_ADE7878_SPI(CVGAIN,4,CorrectReg_cof);	
//  Write_ADE7878_SPI(NIGAIN,4,CorrectReg_cof);
 //功率校准
 /* Write_ADE7878_SPI(AIRMSOS,4,CorrectReg_cof);		   //电压电流有效值校准
  Write_ADE7878_SPI(AVRMSOS,4,CorrectReg_cof);	
  Write_ADE7878_SPI(BIRMSOS,4,CorrectReg_cof);	
  Write_ADE7878_SPI(BVRMSOS,4,CorrectReg_cof);	
  Write_ADE7878_SPI(CIRMSOS,4,CorrectReg_cof);	
  Write_ADE7878_SPI(CVRMSOS,4,CorrectReg_cof);	
  Write_ADE7878_SPI(NIRMSOS,4,CorrectReg_cof);

  Write_ADE7878_SPI(AWGAIN,4,CorrectReg_cof);	   //总有功功率输出波形调整
  Write_ADE7878_SPI(AWATTOS,4,CorrectReg_cof);	   //有功功率失调校准
  Write_ADE7878_SPI(BWGAIN,4,CorrectReg_cof);
  Write_ADE7878_SPI(BWATTOS,4,CorrectReg_cof);
  Write_ADE7878_SPI(CWGAIN,4,CorrectReg_cof);
  Write_ADE7878_SPI(CWATTOS,4,CorrectReg_cof);*/		

//  Write_ADE7878_SPI(CPHCAL,2,CorrectReg_CPHCAL);		//相位校准
//  Write_ADE7878_SPI(BPHCAL,2,CorrectReg_cof);	
//  Write_ADE7878_SPI(CPHCAL,2,CorrectReg_cof);	
}

void ADE7878_init(void)
{
	SPI2_Init();
	ADE7878_GPIOCONFIG();
	ADE7878_PSM0_Enable();
	OSTimeDlyHMSM(0,0,0,40);
	ADE7878_SPI_Enable();
    ADE7878_CORRECTCONFIG();	
	ADE7878_BASICCONFIG();
}



