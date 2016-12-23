
/*
*********************************************************************************************************
*                                             INCLUDE FILES
*********************************************************************************************************
*/
#define GLOBALS

#include "stdarg.h"
 
#include "includes.h"
#include "globals.h"

#include"math.h"

OS_EVENT* Send1_SEM;
OS_EVENT* Send2_MBOX;
OS_EVENT* Send1_c_SEM;

extern unsigned char CIRMSReg[DataBufferSize*4],ICWVReg[4],VCWVReg[4], CWATTHRReg[4],
                     CVRMSReg[DataBufferSize*4], CWATTReg[4],Status_1[4],Status_0[4],
					 VPEAKReg[DataBufferSize*4],IPEAKReg[DataBufferSize*4],MASK0_data[4];
u8 sampleFlag=1,dataflag=21;
u32 test1=0;
s32 iwave=0,vwave=0;
float irms=0,vrms=0,i_RMS=0,i_WAVE=0,v_RMS=0,v_WAVE=0,cwatt=0,C_WATT=0,cwatthr=0,C_WATTHR=0,TEST_1=0;
unsigned char i=0;
u8 testdat[4]={0x00,0x30,0x00,0x00};

/*
*********************************************************************************************************
*                                            LOCAL DEFINES
*********************************************************************************************************
*/



/*
*********************************************************************************************************
*                                       LOCAL GLOBAL VARIABLES
*********************************************************************************************************
*/

static  OS_STK App_TaskStartStk[APP_TASK_START_STK_SIZE];

static  OS_STK Task_Send1Stk[Task_Send1_STK_SIZE];
static  OS_STK Task_Send2Stk[Task_Send2_STK_SIZE];
		
		

/*
*********************************************************************************************************
*                                      LOCAL FUNCTION PROTOTYPES
*********************************************************************************************************
*/
static  void App_TaskCreate(void);

static  void App_TaskStart(void* p_arg);

static  void Task_Send1(void* p_arg);
static  void Task_Send2(void* p_arg);



int main(void)
{
   CPU_INT08U os_err;

   //��ֹCPU�ж�
   CPU_IntDis();
   
   //UCOS ��ʼ��
   OSInit();                                                   /* Initialize "uC/OS-II, The Real-Time Kernel".         */
   
   //Ӳ��ƽ̨��ʼ��
   BSP_Init();     
   
   //���������� ���ȼ����  ���������������һ����;��Ϊ���Ժ�ʹ��ͳ������
   os_err = OSTaskCreate((void (*) (void *)) App_TaskStart,	  		  		//ָ����������ָ��
                          (void *) 0,								  		//����ʼִ��ʱ�����ݸ�����Ĳ�����ָ��
               (OS_STK *) &App_TaskStartStk[APP_TASK_START_STK_SIZE - 1],	//���������Ķ�ջ��ջ��ָ��   �Ӷ����µݼ�
               (INT8U) APP_TASK_START_PRIO);								//�������������ȼ�
   
   //ucos�Ľ��ļ�������0    ���ļ�������0-4294967295    ���ڽ���Ƶ��100hzʱ�� ÿ��497������¼��� 
   OSTimeSet(0);
   OSStart();                                                  /* Start multitasking (i.e. give control to uC/OS-II).  */
                                                 /* Start multitasking (i.e. give control to uC/OS-II).  */
// 
   return (0);
}




/*
*********************************************************************************************************
*                                          App_TaskStart()
*
* Description : The startup task.  The uC/OS-II ticker should only be initialize once multitasking starts.
*
* Argument : p_arg       Argument passed to 'App_TaskStart()' by 'OSTaskCreate()'.
*
* Return   : none.
*
* Caller   : This is a task.
*
* Note     : none.
*********************************************************************************************************
*/

static  void App_TaskStart(void* p_arg)
{
   


   (void) p_arg;

   //��ʼ��ucosʱ�ӽ���
   OS_CPU_SysTickInit();                                       /* Initialize the SysTick.       */

//ʹ��ucos ��ͳ������
#if (OS_TASK_STAT_EN > 0)
   //----ͳ�������ʼ������  
   OSStatInit();                                               /* Determine CPU capacity.                              */
#endif
   //��������������
    
   printf("��ʼ�����");
   OSTimeDlyHMSM(0, 0,1, 0);
   App_TaskCreate();

   while (1)
   {
      //1��һ��ѭ��
	  OSTimeDlyHMSM(0, 0,1, 0);

   }
}



static  void Task_Send1(void* p_arg)
{
	INT8U err;
   (void) p_arg;
   OSSemPost(Send1_c_SEM);
   printf("��ʼ��ȡ \r\n");
   			    
   while (1)
   {
		OSSemPend(Send1_SEM,0,&err);
		
		irms = irms + (CIRMSReg[4*i+3] + CIRMSReg[4*i+2]*256 + CIRMSReg[4*i+1]*65536)*1.0/DataBufferSize;
			 vrms = vrms + (CVRMSReg[4*i+3] + CVRMSReg[4*i+2]*256 + CVRMSReg[4*i+1]*65536)*1.0/DataBufferSize;
			
			if(CWATTReg[1]>=0X80)
			{			
				cwatt = -(16777216*1 - (CWATTReg[1])*65536 - (CWATTReg[2])*256 -(CWATTReg[3]));				
			}
			if(CWATTReg[1]<0X80) 
			{
				cwatt = CWATTReg[3] +  CWATTReg[2]*256 +  CWATTReg[1]*65536;
			}
           
		   
		    /* C�������˲ʱֵ  */
			if(ICWVReg[1]>=0X80)
			{			
				iwave = -(16777216*1 - (ICWVReg[1])*65536 - (ICWVReg[2])*256 -(ICWVReg[3]));				
			}
			if(ICWVReg[1]<0X80) 

			{
				iwave = ICWVReg[3] + ICWVReg[2]*256 + ICWVReg[1]*65536;
			}
	     
		 	/* C���ѹ��˲ʱֵ  */
			if(VCWVReg[1]>=0X80)
			{			
				vwave = -(16777216*1 - (VCWVReg[1])*65536 - (VCWVReg[2])*256 -(VCWVReg[3]));				
			}
			if(VCWVReg[1]<0X80) 
			{
				vwave = VCWVReg[3] + VCWVReg[2]*256 + VCWVReg[1]*65536;
			}
			test1=testdat[3] + testdat[2]*256 + testdat[1]*65536;
			i++;

			if(i==DataBufferSize)
			 {
			
//				i_RMS=(irms/4191910.0) *0.5/sqrt(2.0)/136*2000; //���°��Ӷ�Ӧ��ʽ YK�޸�
				i_RMS=(irms/4191910.0) *0.5/sqrt(2.0)/136*1000;	 //�����˰��Ӷ�Ӧ��ʽ YK 2016.6.23
//			    i_RMS=(irms/4191910.0) *0.5/sqrt(2.0)/36*3000; //���ܲ��� ����ȡ������18ŷķ YK 2016.7.31
				irms=0;

				C_WATT = (cwatt/33516139.0)*2.600*276.341*16;//2016.5.9 YK�޸� �������й�����
//				C_WATT = (cwatt/33516139.0)*29.463*406.383*16;//���ܲ��� ����ȡ������18ŷķ YK 2016.7.31
//              C_WATT = (cwatt/33516139.0)*5.199*276.341*16;//2016.5.9 YK�޸� �������й�����
				cwatt = 0;
		     	
//              v_RMS=(vrms/4191910.0)*0.5/sqrt(2.0)*800;
				v_RMS=(vrms/4191910.0)*0.5/sqrt(2.0)*781.609;
//            	v_RMS=(vrms/4191910.0)*0.5/sqrt(2.0)*1149.425; //���ܲ��� ����ȡ������18ŷķ YK 2016.7.31
				vrms=0;
			
				i_WAVE=(iwave/5928256.0) *0.5*25;
				v_WAVE=(vwave/5928256.0) *0.5*879;
				TEST_1=(test1/5928256.0)*0.5*25;
			
//				printf("\r\n����\r\n");
//			    printf("\r\n������Чֵ10���� %f\r\n",irms);
//	            printf("\r\n������Чֵ #%6.2f",i_RMS);
//				printf("\r\n��ѹ��Чֵʮ���� #%6.2f",vrms);
//              printf("\r\n��ѹ��Чֵ #%6.2f",v_RMS);
//			    printf("\r\n���й����� #%6.2f\r\n",C_WATT);
//			    printf("\r\n���й����ʵ����ۼ� #%6.2f\r\n",A_WATTHR);
//				printf("\r\n��ѹ��Чֵ %6.2f\r\n",v_RMS);
//				printf("\r\n����˲ʱֵ %6.2f\r\n",i_WAVE);
//				printf("\r\n��ѹ˲ʱֵ %6.2f\r\n",v_WAVE);
//			    printf("\r\n����ֵ %6.2f\r\n",TEST_1);
			   	
				i=0;
				OSSemPost(Send1_c_SEM);
   			}
		}
}
static  void Task_Send2(void* p_arg)
{
	INT8U err;
	unsigned char * msg;
   (void) p_arg;	    
   while (1)
   {
		msg=(unsigned char *)OSMboxPend(Send2_MBOX,0,&err);
		
		cwatthr = (msg[3] +  msg[2]*256 +  msg[1]*65536 + msg[0]*16777216)*1.0;
		C_WATTHR=cwatthr*0.001;
//		C_WATTHRFlag=1;
//		printf("\r\n���й����� #%6.2f\r\n",C_WATTHR);
       
	    if(C_WATT<1000)
		printf("S#E04#%6.2f#%6.2f#%6.2f#%6.2f#E",v_RMS,i_RMS,C_WATT,C_WATTHR);
		else
		printf("S#E04#%6.2f#%6.2f#%6.1f#%6.2f#E",v_RMS,i_RMS,C_WATT,C_WATTHR);
		//USART_OUT(USART1,"��������2");
   }
}


/*
*********************************************************************************************************
*                                            App_TaskCreate()
*
* Description : Create the application tasks.
*
* Argument : none.
*
* Return   : none.
*
* Caller   : App_TaskStart().
*
* Note     : none.
*********************************************************************************************************
*/

static  void App_TaskCreate(void)
{
    //CPU_INT08U os_err;
 
   Send1_SEM=OSSemCreate(1);
   Send1_c_SEM=OSSemCreate(1);		     //�������ź���

   Send2_MBOX=OSMboxCreate((void *) 0);		     //������Ϣ����
   

   
   
   //Send1���ռ���������---------------------------------------------------------    
   OSTaskCreateExt(Task_Send1,									  //ָ����������ָ��
   					(void *)0,									  //����ʼִ��ʱ�����ݸ�����Ĳ�����ָ��
					(OS_STK *)&Task_Send1Stk[Task_Send1_STK_SIZE-1],//���������Ķ�ջ��ջ��ָ��   �Ӷ����µݼ�
					Task_Send1_PRIO,								  //�������������ȼ�
					Task_Send1_PRIO,								  //Ԥ�����Ժ�汾�������ʶ���������а汾ͬ�������ȼ�
					(OS_STK *)&Task_Send1Stk[0],					  //ָ�������ջջ�׵�ָ�룬���ڶ�ջ�ļ���
                    Task_Send1_STK_SIZE,							  //ָ����ջ�����������ڶ�ջ�ļ���
                    (void *)0,									  //ָ���û����ӵ��������ָ�룬������չ�����������ƿ�
                    OS_TASK_OPT_STK_CHK|OS_TASK_OPT_STK_CLR);	  //ѡ�ָ���Ƿ������ջ���飬�Ƿ񽫶�ջ��0,�����Ƿ�Ҫ���и�������ȵȡ�
   //Send2����------------------------------------------------------
    OSTaskCreateExt(Task_Send2,									  //ָ����������ָ��
   					(void *)0,									  //����ʼִ��ʱ�����ݸ�����Ĳ�����ָ��
					(OS_STK *)&Task_Send2Stk[Task_Send2_STK_SIZE-1],//���������Ķ�ջ��ջ��ָ��   �Ӷ����µݼ�
					Task_Send2_PRIO,								  //�������������ȼ�
					Task_Send2_PRIO,								  //Ԥ�����Ժ�汾�������ʶ���������а汾ͬ�������ȼ�
					(OS_STK *)&Task_Send2Stk[0],					  //ָ�������ջջ�׵�ָ�룬���ڶ�ջ�ļ���
                    Task_Send2_STK_SIZE,							  //ָ����ջ�����������ڶ�ջ�ļ���
                    (void *)0,									  //ָ���û����ӵ��������ָ�룬������չ�����������ƿ�
                    OS_TASK_OPT_STK_CHK|OS_TASK_OPT_STK_CLR);	  //ѡ�ָ���Ƿ������ջ���飬�Ƿ񽫶�ջ��0,�����Ƿ�Ҫ���и�������ȵȡ�
      
}




/*
*********************************************************************************************************
*********************************************************************************************************
*                                          uC/OS-II APP HOOKS
*********************************************************************************************************
*********************************************************************************************************
*/

#if (OS_APP_HOOKS_EN > 0)
/*
*********************************************************************************************************
*                                      TASK CREATION HOOK (APPLICATION)
*
* Description : This function is called when a task is created.
*
* Argument : ptcb   is a pointer to the task control block of the task being created.
*
* Note     : (1) Interrupts are disabled during this call.
*********************************************************************************************************
*/

void App_TaskCreateHook(OS_TCB* ptcb)
{
}

/*
*********************************************************************************************************
*                                    TASK DELETION HOOK (APPLICATION)
*
* Description : This function is called when a task is deleted.
*
* Argument : ptcb   is a pointer to the task control block of the task being deleted.
*
* Note     : (1) Interrupts are disabled during this call.
*********************************************************************************************************
*/

void App_TaskDelHook(OS_TCB* ptcb)
{
   (void) ptcb;
}

/*
*********************************************************************************************************
*                                      IDLE TASK HOOK (APPLICATION)
*
* Description : This function is called by OSTaskIdleHook(), which is called by the idle task.  This hook
*               has been added to allow you to do such things as STOP the CPU to conserve power.
*
* Argument : none.
*
* Note     : (1) Interrupts are enabled during this call.
*********************************************************************************************************
*/

#if OS_VERSION >= 251
void App_TaskIdleHook(void)
{
}
#endif

/*
*********************************************************************************************************
*                                        STATISTIC TASK HOOK (APPLICATION)
*
* Description : This function is called by OSTaskStatHook(), which is called every second by uC/OS-II's
*               statistics task.  This allows your application to add functionality to the statistics task.
*
* Argument : none.
*********************************************************************************************************
*/

void App_TaskStatHook(void)
{
}

/*
*********************************************************************************************************
*                                        TASK SWITCH HOOK (APPLICATION)
*
* Description : This function is called when a task switch is performed.  This allows you to perform other
*               operations during a context switch.
*
* Argument : none.
*
* Note     : 1 Interrupts are disabled during this call.
*
*            2  It is assumed that the global pointer 'OSTCBHighRdy' points to the TCB of the task that
*                   will be 'switched in' (i.e. the highest priority task) and, 'OSTCBCur' points to the
*                  task being switched out (i.e. the preempted task).
*********************************************************************************************************
*/

#if OS_TASK_SW_HOOK_EN > 0
void App_TaskSwHook(void)
{
}
#endif

/*
*********************************************************************************************************
*                                     OS_TCBInit() HOOK (APPLICATION)
*
* Description : This function is called by OSTCBInitHook(), which is called by OS_TCBInit() after setting
*               up most of the TCB.
*
* Argument : ptcb    is a pointer to the TCB of the task being created.
*
* Note     : (1) Interrupts may or may not be ENABLED during this call.
*********************************************************************************************************
*/

#if OS_VERSION >= 204
void App_TCBInitHook(OS_TCB* ptcb)
{
   (void) ptcb;
}
#endif

#endif
