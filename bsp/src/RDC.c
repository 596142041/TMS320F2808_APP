/********************************************************
 *文件名:RDC.c
 *创建时间:2018-10-09
 *作者: 皇甫仁和
 ********************************************************/
#include "RDC.h"
#define RDC_SAMPLE GpioDataRegs.GPADAT.bit.GPIO11
#define RDC_CS     GpioDataRegs.GPADAT.bit.GPIO15
RDC_DATA RDC_data;
void RDC_GPIO_Config(void)
{
	EALLOW;
    GpioCtrlRegs.GPAPUD.bit.GPIO13 = 0;     // Enable pull-up on GPIO13 (SPISOMIB)

    GpioCtrlRegs.GPAPUD.bit.GPIO14 = 0;     // Enable pull-up on GPIO14 (SPICLKB)

    GpioCtrlRegs.GPAPUD.bit.GPIO15 = 0;     // Enable pull-up on GPIO15 (SPISTEB)

    GpioCtrlRegs.GPAQSEL1.bit.GPIO13 = 3;   // Asynch input GPIO13 (SPISOMIB)

    GpioCtrlRegs.GPAQSEL1.bit.GPIO14 = 3;   // Asynch input GPIO14 (SPICLKB)

    GpioCtrlRegs.GPAQSEL1.bit.GPIO15 = 3;   // Asynch input GPIO15 (SPISTEB)

    GpioCtrlRegs.GPAMUX1.bit.GPIO13 = 3;    // Configure GPIO13 as SPISOMIB

    GpioCtrlRegs.GPAMUX1.bit.GPIO14 = 3;    // Configure GPIO14 as SPICLKB

    GpioCtrlRegs.GPAMUX1.bit.GPIO15 = 3;    // Configure GPIO15 as SPISTEB
//-----------------------------------------------------------------------
    //--RDC_SAMPLE配置
    GpioCtrlRegs.GPADIR.bit.GPIO11 = GPIO_Mode_OUT;
    GpioCtrlRegs.GPAPUD.bit.GPIO11 = 0;
    GpioCtrlRegs.GPAMUX1.bit.GPIO11 = 0;
    EDIS;
    GpioDataRegs.GPADAT.bit.GPIO11 = 1;
    GpioDataRegs.GPADAT.bit.GPIO15 = 1;
}
void RDC_SPI_Config(void)
{
	EALLOW;
	SysCtrlRegs.PCLKCR0.bit.SPIBENCLK =1;
	EDIS;
	SpibRegs.SPICCR.bit.SPISWRESET=0; // Reset SPI
	SpibRegs.SPICCR.all=0x004F;       // 16-bit character, Loopback mode disabled
	SpibRegs.SPICTL.all=0x0004;       // SPI Interrupt disabled, Master mode, Master/slave transmit enabled
	SpibRegs.SPIBRR=0x0025;           // 0.9615M, SPI Baud rate=LSPCLK/(SPIBRR+1), here, LSPCLK=37.5M, SPIBRR=38
	SpibRegs.SPIPRI.all=0x0010;
	SpibRegs.SPICCR.bit.SPISWRESET=1; // Enable SPI
}
void Read_RDC_data(RDC_DATA *data)
{
RDC_CS = 0;
RDC_SAMPLE = 0;
	delay_us(0xc8);
	SpibRegs.SPITXBUF=0xFFFF;   //start SPI transmit once
	while (SpibRegs.SPISTS.bit.INT_FLAG == 0)
	{ /*NOP*/ }
	data->all = SpibRegs.SPIRXBUF;
	RDC_CS = 1;
	RDC_SAMPLE = 1;
}
