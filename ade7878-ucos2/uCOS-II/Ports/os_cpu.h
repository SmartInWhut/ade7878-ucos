/*
*********************************************************************************************************
*                                               uC/OS-II
*                                         The Real-Time Kernel
*
*
*                                (c) Copyright 2006, Micrium, Weston, FL
*                                          All Rights Reserved
*
*                                           ARM Cortex-M3 Port
*
* File      : OS_CPU.H
* Version   : V2.86
* By        : Jean J. Labrosse
*
* For       : ARMv7M Cortex-M3
* Mode      : Thumb2
* Toolchain : RealView Development Suite
*             RealView Microcontroller Development Kit (MDK)
*             ARM Developer Suite (ADS)
*             Keil uVision
*********************************************************************************************************
*/

#ifndef  OS_CPU_H
#define  OS_CPU_H


#ifdef   OS_CPU_GLOBALS			   //允许我们是否使用全局变量
#define  OS_CPU_EXT
#else
#define  OS_CPU_EXT  extern
#endif

/*
*********************************************************************************************************
*                                              DATA TYPES
*                                         (Compiler Specific)
*********************************************************************************************************
*/

typedef unsigned char  BOOLEAN;
typedef unsigned char  INT8U;                    /* Unsigned  8 bit quantity                           */
typedef signed   char  INT8S;                    /* Signed    8 bit quantity                           */
typedef unsigned short INT16U;                   /* Unsigned 16 bit quantity                           */
typedef signed   short INT16S;                   /* Signed   16 bit quantity                           */
typedef unsigned long  INT32U;                   /* Unsigned 32 bit quantity                           */
typedef signed   long  INT32S;                   /* Signed   32 bit quantity                           */
typedef float          FP32;                     /* Single precision floating point                    */
typedef double         FP64;                     /* Double precision floating point                    */

typedef unsigned int   OS_STK;                   /* Each stack entry is 32-bit wide                    */
typedef unsigned int   OS_CPU_SR;                /* Define size of CPU status register (PSR = 32 bits) */





/*
*********************************************************************************************************
*                                              Cortex-M1
*                                      Critical Section Management
*
* Method #1:  Disable/Enable interrupts using simple instructions.  After critical section, interrupts
*             will be enabled even if they were disabled before entering the critical section.
*             NOT IMPLEMENTED
*
* Method #2:  Disable/Enable interrupts by preserving the state of interrupts.  In other words, if
*             interrupts were disabled before entering the critical section, they will be disabled when
*             leaving the critical section.
*             NOT IMPLEMENTED
*
* Method #3:  Disable/Enable interrupts by preserving the state of interrupts.  Generally speaking you
*             would store the state of the interrupt disable flag in the local variable 'cpu_sr' and then
*             disable interrupts.  'cpu_sr' is allocated in all of uC/OS-II's functions that need to
*             disable interrupts.  You would restore the interrupt disable state by copying back 'cpu_sr'
*             into the CPU's status register.
*********************************************************************************************************
*/

#define  OS_CRITICAL_METHOD   3


#if OS_CRITICAL_METHOD == 3	  //进入临界段的三种模式，一般选择第 3 种，即这里设置为3
#define  OS_ENTER_CRITICAL()  {cpu_sr = OS_CPU_SR_Save();}	  //进入临界段，关中断
#define  OS_EXIT_CRITICAL()   {OS_CPU_SR_Restore(cpu_sr);}	  //退出临界段，开中断
#endif










/*
*********************************************************************************************************
*                                        Cortex-M3 Miscellaneous
*********************************************************************************************************
*/

#define  OS_STK_GROWTH        1                   /* Stack grows from HIGH to LOW memory on ARM      */

#define  OS_TASK_SW()         OSCtxSw()







/*
*********************************************************************************************************
*                                              PROTOTYPES
*********************************************************************************************************
*/

#if OS_CRITICAL_METHOD == 3                       /* See OS_CPU_A.ASM                                  */
OS_CPU_SR  OS_CPU_SR_Save(void);
void       OS_CPU_SR_Restore(OS_CPU_SR cpu_sr);
#endif

void       OSCtxSw(void);			  //用户任务切换
void       OSIntCtxSw(void);		  //中断任务切换函数
void       OSStartHighRdy(void);	  //在操作系统第一次启动的时候调用的任务切换

void       OSPendSV(void);			  /*用户中断处理函数，有的版本是OS_CPU_PendSVHandler(void)。它是可以像普通的中断一样被悬起,
OS可以利用它“缓期执行”一个异常，直到其它重要的任务完成后才执行动作。悬起 PendSV 的方法是：手工往 NVIC 的 PendSV 悬起寄存器中
写1。悬起后，如果优先级不够高，则将缓期等待执行。
PendSV 的典型使用场合是在上下文切换时（在不同任务之间切换）
*/
#endif
