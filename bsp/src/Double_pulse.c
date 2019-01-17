/**********************************************
 * Double_pulse.c
 * Created on: 2019年1月16日
 * Author: admin
 * Version:
 ************************************************/
#include "Double_pulse.h"
Double_pulse_Mode run_mode = Stop;
void Double_pulse_GPIO_init(void)
{
    //--------------------------
    EALLOW;
    GpioCtrlRegs.GPAPUD.bit.GPIO0 = 0;    // Enable pull-up on GPIO0 (EPWM1A)
    GpioCtrlRegs.GPAPUD.bit.GPIO1 = 0;    // Enable pull-up on GPIO1 (EPWM1B)
    GpioCtrlRegs.GPAMUX1.bit.GPIO0 = 0;   // Configure GPIO0 as EPWM1A
    GpioCtrlRegs.GPAMUX1.bit.GPIO1 = 0;   // Configure GPIO1 as EPWM1B
    GpioCtrlRegs.GPADIR.bit.GPIO0 = GPIO_Mode_OUT;
    GpioCtrlRegs.GPADIR.bit.GPIO1 = GPIO_Mode_OUT;

    GpioCtrlRegs.GPAPUD.bit.GPIO2 = 0;    // Enable pull-up on GPIO2 (EPWM2A)
    GpioCtrlRegs.GPAPUD.bit.GPIO3 = 0;    // Enable pull-up on GPIO3 (EPWM3B)
    GpioCtrlRegs.GPAMUX1.bit.GPIO2 = 0;   // Configure GPIO2 as EPWM2A
    GpioCtrlRegs.GPAMUX1.bit.GPIO3 = 0;   // Configure GPIO3 as EPWM2B
    GpioCtrlRegs.GPADIR.bit.GPIO2 = GPIO_Mode_OUT;
    GpioCtrlRegs.GPADIR.bit.GPIO3 = GPIO_Mode_OUT;

    GpioCtrlRegs.GPAPUD.bit.GPIO4 = 0;    // Enable pull-up on GPIO4 (EPWM3A)
    GpioCtrlRegs.GPAPUD.bit.GPIO5 = 0;    // Enable pull-up on GPIO5 (EPWM3B)
    GpioCtrlRegs.GPAMUX1.bit.GPIO4 = 0;   // Configure GPIO4 as EPWM3A
    GpioCtrlRegs.GPAMUX1.bit.GPIO5 = 0;   // Configure GPIO5 as EPWM3B
    GpioCtrlRegs.GPADIR.bit.GPIO4 = GPIO_Mode_OUT;
    GpioCtrlRegs.GPADIR.bit.GPIO5 = GPIO_Mode_OUT;
    //------------------TZ1引脚配置-----------------------
//  GpioCtrlRegs.GPAPUD.bit.GPIO12 = 0;    // Enable pull-up on GPIO12 (TZ1)
//  GpioCtrlRegs.GPAQSEL1.bit.GPIO12 = 3;  // Asynch input GPIO12 (TZ1)
//  GpioCtrlRegs.GPAMUX1.bit.GPIO12 = 1;  // Configure GPIO12 as TZ1
    EDIS;
}
/******************************************************************************
 * 函数名:void Double_pulse_run(Double_pulse_Mode mode,u8 channel,u8 t1,u8 t2, u8 t3)
 * 输入参数:
 * Double_pulse_Mode mode:表示当前的脉冲模式,包括:停止,单脉冲模式,双脉冲模式,连续模式(PWM模式);
 *   ________        ___________
 *  |        |       |         |
 *  |        |       |         |
 *  |        |       |         |
 *  |        |       |         |
 *  |   t1   |___t2__|  t3     |
 *******************************************************************************/
void Double_pulse_run(Double_pulse_Mode mode,u8 channel,u16 t1,u16 t2, u16 t3)
{

}



