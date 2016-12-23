																	   
#ifndef _ADE7878_H
#define _ADE7878_H

#include"stm32f10x.h"

//the addresses of all ADE78xx registers
#define   AIGAIN            0x4380
#define   AVGAIN            0x4381
#define   BIGAIN            0x4382
#define   BVGAIN            0x4383
#define   CIGAIN            0x4384
#define   CVGAIN            0x4385
#define   NIGAIN            0x4386	   //���ߵ����������
#define   AIRMSOS           0x4387
#define   AVRMSOS           0x4388
#define   BIRMSOS           0x4389
#define   BVRMSOS           0x438A
#define   CIRMSOS           0x438B
#define   CVRMSOS           0x438C
#define   NIRMSOS           0x438D	   //���ߵ�����Чֵƫ��ʧ��
#define   AVAGAIN           0X438E	   //XXX���ڹ����������
#define   BVAGAIN           0X438F
#define   CVAGAIN           0X4390
#define   AWGAIN            0X4391	   //XXX���й������������
#define   AWATTOS           0x4392	   //XXX���й�����ƫ��ʧ������
#define   BWGAIN            0X4393
#define   BWATTOS           0x4394
#define   CWGAIN            0X4395
#define   CWATTOS           0x4396
#define   AVARGAIN          0X4397
#define   AVAROS            0x4398
#define   BVARGAIN  		0X4399
#define   BVAROS            0x439A
#define   CVARGAIN          0X439B
#define   CVAROS            0x439C
#define   AFWGAIN	        0X439D	      //XXX�����й������������  
#define   AFWATTOS          0x439E		  //XXX�����й�����ƫ��ʧ������
#define   BFWGAIN           0X439F
#define   BFWATTOS          0x43A0
#define   CFWGAIN           0X43A1
#define   CFWATTOS          0x43A2
#define   AFVARGAIN			0X43A3
#define   AFVAROS           0x43A4
#define   BFVARGAIN         0X43A5
#define   BFVAROS           0x43A6
#define   CFVARGAIN			0X43A7
#define   CFVAROS           0x43A8
#define   VATHR1            0x43A9			//��λ���ڹ�������·��������VATHR[47:0]��ֵ��24�������Чλ
#define   VATHR0            0x43AA			//��λ���ڹ�������·��������VATHR[47:0]��ֵ��24�������Чλ
#define   WTHR1             0x43AB			//��λ��/�����й���������·��������WTHR[47:0]��ֵ��24�������Чλ
#define   WTHR0             0x43AC			//��λ��/�����й���������·��������WTHR[47:0]��ֵ��24�������Чλ
#define   VARTHR1           0x43AD			//��λ��/�����޹���������·��������VARTHR[47:0]��ֵ��24�������Чλ
#define   VARTHR0           0x43AE			//��λ��/�����޹���������·��������VARTHR[47:0]��ֵ��24�������Чλ

#define   VANOLOAD          0x43B0			//���ڹ�������·���еĿ�����ֵ
#define   APNOLOAD          0x43B1			//��/�����й���������·���еĿ�����ֵ
#define   VARNOLOAD         0x43B2			//��/�����޹���������·���еĿ�����ֵ
#define   VLEVEL            0x43B3			//�����й�/�޹������㷨��ʹ�õļĴ���
#define   DICOEFF           0x43B5   		//���ֻ������㷨��ʹ�õļĴ���������������ڿ���״̬���������Ϊ0xFF8000
#define   HPFDIS		    0X43B6		    //����/ʹ�ܵ�������·���е�HPF
#define   ISUMLVL           0x43B8			//�Ƚ������֮�ͺ����ߵ���ʱʹ�õ���ֵ
#define   ISUM              0x43BF
#define   AIRMS             0x43C0			  //XX������Чֵ
#define   AVRMS             0x43C1
#define   BIRMS             0x43C2
#define   BVRMS             0x43C3			   //XX��ѹ��Чֵ
#define   CIRMS             0x43C4
#define   CVRMS             0x43C5
#define   NIRMS             0x43C6

#define   RUN               0xE228			   //Run�Ĵ���������ͣDSP
//Billable Registers
#define   AWATTHR           0xE400			   
#define   BWATTHR           0xE401			   //XX���й������ۼ�
#define   CWATTHR           0xE402
#define   AFWATTHR          0xE403
#define   BFWATTHR          0xE404			   //XX�����й������ۼ�
#define   CFWATTHR          0xE405
#define   AVARHR            0xE406
#define   BVARHR            0xE407				//XX���޹������ۼ�
#define   CVARHR            0xE408
#define   AFVARHR           0xE409
#define   BFVARHR           0xE40A				//XX�����޹������ۼ�
#define   CFVARHR           0xE40B
#define   AVAHR             0xE40C			    //���ڵ����ۼ�
#define   BVAHR             0xE40D
#define   CVAHR             0xE40E

//Configuration and Power Quality Resisiters
#define   IPEAK             0xE500				 //Current peak�Ĵ���
#define   VPEAK             0xE501				 //Voltage peak�Ĵ���
#define   STATUS0           0xE502				 //interrupt status�Ĵ���0
#define   STATUS1           0xE503				 //interrupt status�Ĵ���1
#define   AIMAV             0xE504				 
#define   BIMAV             0xE505				 //PSM0��PSM1ģʽ�¼������XX����ƽ������ֵ
#define   CIMAV             0xE506
#define   OILVL             0xE507				 //������ֵ
#define   OVLVL             0xE508				 //��ѹ��ֵ
#define   SAGLVL            0xE509				 //��ѹSAG��ƽ��ֵ
#define   MASK0             0xE50A				 //interrupt enable�Ĵ���0
#define   MASK1             0xE50B				 //interrupt enable�Ĵ���1
#define   IAWV              0xE50C
#define   IBWV              0xE50D				 //XX������˲ʱֵ
#define   ICWV              0xE50E
#define   INWV              0xE50F				 //���ߵ�����˲ʱֵ
#define   VAWV              0xE510
#define   VBWV              0xE511				  //XX��ѹ��˲ʱֵ
#define   VCWV              0xE512
#define   AWATT             0xE513
#define   BWATT             0xE514				   //XX���й����ʵ�˲ʱֵ
#define   CWATT             0xE515
#define   AVAR              0xE516
#define   BVAR              0xE517				   //XX���޹����ʵ�˲ʱֵ
#define   CVAR              0xE518
#define   AVA               0xE519
#define   BVA               0xE51A				   //XX���ڹ��ʵ�˲ʱֵ
#define   CVA               0xE51B
#define   CHECKSUM          0xE51F				   //�������֤
#define   VNOM              0xE520				   //���ڹ������������ʹ�õı�����ѹ��Чֵ����Щ��ַ��Ӧд�����ݣ��Ա���������

//16bits resisiter
#define   PHSTATUS          0xE600				   //phase peak�Ĵ���
#define   ANGLE0            0xE601
#define   ANGLE1            0xE602				   //ʱ���ӳ�x
#define   ANGLE2            0xE603
#define   PERIOD            0xE607				   //����������
#define   PHNOLOAD          0xE608				   //Phase Noload�Ĵ���
#define   LINECYC           0xE60C				   //�������ۼ�ģʽ����
#define   ZXTOUT            0xE60D				   //���㳬ʱ����
#define   COMPMODE          0xE60E				   //Computation-mode�Ĵ���
#define   GAIN              0xE60F				   //���棬ADC����˵�PGA����
#define   CFMODE            0xE610				   //CFx conguration�Ĵ���
#define   CF1DEN            0xE611
#define   CF2DEN            0xE612				   //CFx��ĸ
#define   CF3DEN            0xE613
#define   APHCAL            0xE614
#define   BPHCAL            0xE615				   //xx��λУ׼
#define   CPHCAL            0xE616
#define   PHSIGN            0xE617				   //Power sign�Ĵ���
#define   CONFIG            0xE618				   //ADE7878 configuration�Ĵ���

//8bits reister
#define   MMODE             0xE700				   //Measurement mode�Ĵ���
#define   ACCMODE           0xE701				   //Accumulation mode�Ĵ���
#define   LCYCMODE          0xE702				   //��·�ۼ�ģʽ״̬
#define   PEAKCYC           0xE703				   //��ֵ���벨������
#define   SAGCYC            0xE704				   //SAG���벨������
#define   CFCYC             0xE705				   //����������������֮���CF������
#define   HSDC_CFG          0xE706				   //HSDC conguration�Ĵ���
#define   LPOILVL           0xEC00				   //PSM2ģʽ��ʹ�õĹ�����ֵ
#define   CONFIG2           0xEC01				   //PSM1ģʽ��ʹ�õ�configuration�Ĵ���

#define ADE_PM0_0    GPIO_ResetBits(GPIOD,GPIO_Pin_15)    //PM0<=>GPIOD_Pin_15
#define ADE_PM0_1    GPIO_SetBits(GPIOD,GPIO_Pin_15)
#define ADE_PM1_0  	 GPIO_ResetBits(GPIOD,GPIO_Pin_14)	  //PM1<=>GPIOD_Pin_14
#define ADE_PM1_1    GPIO_SetBits(GPIOD,GPIO_Pin_14)
#define ADE_RESET_0  GPIO_ResetBits(GPIOD,GPIO_Pin_13)	  //RESET<=>PD13
#define ADE_RESET_1  GPIO_SetBits(GPIOD,GPIO_Pin_13)
#define ADE_CS_0	 GPIO_ResetBits(GPIOB,GPIO_Pin_12)	  //CS<=>PB12
#define ADE_CS_1	 GPIO_SetBits(GPIOB,GPIO_Pin_12)

#define AlarmV 0x30
#define AlarmI 0X31
#define AlarmS 0x32 

void ADE7878_init(void);
void Write_ADE7878_SPI(unsigned int ADE_Addr,unsigned char Nr_Bytes,unsigned char *pReg_Data);
void Read_ADE7878_SPI(unsigned int ADE_Addr, unsigned char Nr_Bytes,unsigned char *pReg_Data);

#endif


















