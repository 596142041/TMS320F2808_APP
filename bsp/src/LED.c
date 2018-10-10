/********************************************************
 *文件名:LED.c
 *创建时间:2018-10-09
 *作者: 皇甫仁和
 ********************************************************/
#include "LED.h"
UPDATA_INFO updata_info =
{
		.time_cnt = 0,
		.time_out_flag = 0,
};
void LED_GPIO_Config(void)
{
	   EALLOW;
		   GpioCtrlRegs.GPAMUX2.bit.GPIO23 = 0;
		   GpioCtrlRegs.GPADIR.bit.GPIO23 = 1;
	   EDIS;
	   GpioDataRegs.GPASET.bit.GPIO23 = 1;
}
void LED_Timer_Config(void)
{
	InitCpuTimers();
	ConfigCpuTimer(&CpuTimer0, 100, 500000);//250ms
	CpuTimer0Regs.TCR.all = 0x4001; // Use write-only instruction to set TSS bit = 0
	 CpuTimer0.InterruptCount = 0;


}
interrupt void cpu_timer0_isr(void)
{
   CpuTimer0.InterruptCount++;
   if(updata_info.time_out_flag == 0)
   {
	   if( CpuTimer0.InterruptCount == 10)
	     {
	  	   updata_info.time_cnt++;
	  	 CpuTimer0.InterruptCount = 0;
	  	   if(updata_info.time_cnt == 10)
	  	   {
	  		   updata_info.time_out_flag = 1;
	  	   }
	     }
   }
   GpioDataRegs.GPATOGGLE.bit.GPIO23 = 1;
   PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;
}


