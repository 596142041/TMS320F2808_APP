/********************************************************
 *文件名:main.c
 *创建时间:2018-10-09
 *作者: 皇甫仁和
 ********************************************************/
/*
 * 生成bin文件参考如下命令:
 "${CCE_INSTALL_ROOT}/utils/tiobj2bin/tiobj2bin.bat" "${BuildArtifactFileName}"
 "${BuildArtifactFileBaseName}.bin" "${CG_TOOL_ROOT}/bin/ofd2000.exe"
 "${CG_TOOL_ROOT}/bin/hex2000.exe" "${CCE_INSTALL_ROOT}/utils/tiobj2bin/mkhex4bin.exe"
 */
#include "main.h"
#include "LED.h"
#include "CANA.h"
#include "delay.h"
#include "ADC.h"
#include "CAN_APP.h"
Sys_Register sys_reg;
void PT100_GPIO_config(void);
void PT100(u8 pt100);
Real_value real_value;
float PTC_in   = 0;
float PTC_res  = 0;
u8 pt100_state = 0;
FLASH_ST Flash_Status;
Uint16 flash_ret = STATUS_SUCCESS;
void main(void)
{
	InitSysCtrl();
	DINT;
	LED_GPIO_Config();
	CAN_GPIO_Config(CANA);
	InitPieCtrl();
	IER = 0x0000;
	IFR = 0x0000;
	InitPieVectTable();
	MemCopy(&RamfuncsLoadStart, &RamfuncsLoadEnd, &RamfuncsRunStart);
	MemCopy(&Flash28_API_LoadStart, &Flash28_API_LoadEnd,&Flash28_API_RunStart);//
	InitFlash();
	FlashAPI_Init();
	//用来标示当前是否app应用层
	flash_ret =Flash_Verify((Uint16 *)APP_INFO_ADDR,app_check,2,&Flash_Status);
	if(flash_ret !=STATUS_SUCCESS )//说明是第一次运行app
	{
	    __set_PRIMASK(1);
	    Flash_WR(APP_INFO_ADDR,app_check,2);
	    __set_PRIMASK(0);
	}

	EALLOW;
	PieVectTable.TINT0     = &cpu_timer0_isr;
	PieVectTable.ECAN1INTA = &Ecana_isr1;
	EDIS;
	ADC_Config();
	CAN_Config(CANA,250);
	CAN_Rx_Config();
	CAN_Rx_IT_Concig();
	LED_Timer_Config();
    PieCtrlRegs.PIEIER1.bit.INTx7 = 1;
    PieCtrlRegs.PIEIER9.bit.INTx6 = 1; //CANA的中断1
    IER |= M_INT9;
    IER |= M_INT1;
    __enable_irq();
	while(1)
	{
	    if(can_rx_msg.rx_update == UPDATE)
        {
            can_rx_msg.rx_update = NON_CHANGE;
            CAN_BOOT_ExecutiveCommand(&can_rx_msg);
        }
        PT100(pt100_state);
        while (AdcRegs.ADCST.bit.INT_SEQ1== 0) ;
        AdcRegs.ADCST.bit.INT_SEQ1_CLR = 1;
        ADC_Calc(&sample_value.sample_value,&ADC_ValueReg.REG);
        real_value.real_Value_24V = sample_value.sample_value.Sampl_Value_24V*12;
        real_value.real_Value_5V  = sample_value.sample_value.Sampl_Value_5V*2;
        real_value.real_Value_AI1 = sample_value.sample_value.Sampl_Value_AI1*25/15.0;
        real_value.real_Value_AI2 = sample_value.sample_value.Sampl_Value_AI2*25/15.0;
        //PTC/32-5V*85/5184
        PTC_in = sample_value.sample_value.Sampl_Value_PTC/(32.0)+sample_value.sample_value.Sampl_Value_5V*2*84.848/(float)5184.848;
        PTC_res=(float)5100/(float)((sample_value.sample_value.Sampl_Value_5V*2.0/PTC_in)-1);
	}


}
void PT100_GPIO_config(void)
{
    EALLOW;
    GpioCtrlRegs.GPADIR.bit.GPIO22 = GPIO_Mode_OUT;
    GpioCtrlRegs.GPAMUX2.bit.GPIO22 = 0;
    GpioCtrlRegs.GPAPUD.bit.GPIO22 = GPIO_PuPd_UP;
    EDIS;
}
void PT100(u8 pt100)
{
    if(pt100 == 1)
    {
        GpioDataRegs.GPASET.bit.GPIO22 = 1;
    }
    else
    {
        GpioDataRegs.GPACLEAR.bit.GPIO22 = 1;
    }
}
