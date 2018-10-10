/********************************************************
 *文件名:EPWM.c
 *创建时间:2018-10-09
 *作者: 皇甫仁和
 ********************************************************/
#include "EPWM.h"
#define table_size 360
unsigned short int sin_tabele[table_size] =
{ 2778, 2801, 2825, 2848, 2871, 2895, 2918, 2941, 2964, 2987, 3010, 3033, 3056,
		3079, 3101, 3124, 3147, 3169, 3191, 3213, 3235, 3257, 3279, 3300, 3322,
		3343, 3364, 3385, 3406, 3426, 3446, 3466, 3486, 3506, 3525, 3545, 3564,
		3582, 3601, 3619, 3637, 3655, 3672, 3689, 3706, 3723, 3739, 3755, 3771,
		3786, 3802, 3816, 3831, 3845, 3859, 3872, 3885, 3898, 3911, 3923, 3935,
		3946, 3957, 3968, 3978, 3988, 3998, 4007, 4016, 4024, 4033, 4040, 4048,
		4055, 4061, 4067, 4073, 4078, 4083, 4088, 4092, 4096, 4099, 4102, 4105,
		4107, 4109, 4110, 4111, 4111, 4111, 4111, 4110, 4109, 4108, 4106, 4103,
		4101, 4098, 4094, 4090, 4086, 4081, 4076, 4070, 4064, 4058, 4051, 4044,
		4036, 4029, 4020, 4012, 4003, 3993, 3983, 3973, 3963, 3952, 3940, 3929,
		3917, 3905, 3892, 3879, 3866, 3852, 3838, 3824, 3809, 3794, 3779, 3763,
		3747, 3731, 3715, 3698, 3681, 3664, 3646, 3628, 3610, 3592, 3573, 3554,
		3535, 3516, 3496, 3476, 3456, 3436, 3416, 3395, 3375, 3354, 3332, 3311,
		3290, 3268, 3246, 3224, 3202, 3180, 3158, 3135, 3113, 3090, 3067, 3045,
		3022, 2999, 2976, 2953, 2929, 2906, 2883, 2860, 2836, 2813, 2790, 2766,
		2743, 2720, 2696, 2673, 2650, 2627, 2603, 2580, 2557, 2534, 2511, 2489,
		2466, 2443, 2421, 2398, 2376, 2354, 2332, 2310, 2288, 2266, 2245, 2224,
		2202, 2181, 2161, 2140, 2120, 2100, 2080, 2060, 2040, 2021, 2002, 1983,
		1964, 1946, 1928, 1910, 1892, 1875, 1858, 1841, 1825, 1809, 1793, 1777,
		1762, 1747, 1732, 1718, 1704, 1690, 1677, 1664, 1651, 1639, 1627, 1616,
		1604, 1593, 1583, 1573, 1563, 1553, 1544, 1536, 1527, 1520, 1512, 1505,
		1498, 1492, 1486, 1480, 1475, 1470, 1466, 1462, 1458, 1455, 1453, 1450,
		1448, 1447, 1446, 1445, 1445, 1445, 1445, 1446, 1447, 1449, 1451, 1454,
		1457, 1460, 1464, 1468, 1473, 1478, 1483, 1489, 1495, 1501, 1508, 1516,
		1523, 1532, 1540, 1549, 1558, 1568, 1578, 1588, 1599, 1610, 1621, 1633,
		1645, 1658, 1671, 1684, 1697, 1711, 1725, 1740, 1754, 1770, 1785, 1801,
		1817, 1833, 1850, 1867, 1884, 1901, 1919, 1937, 1955, 1974, 1992, 2011,
		2031, 2050, 2070, 2090, 2110, 2130, 2150, 2171, 2192, 2213, 2234, 2256,
		2277, 2299, 2321, 2343, 2365, 2387, 2409, 2432, 2455, 2477, 2500, 2523,
		2546, 2569, 2592, 2615, 2638, 2661, 2685, 2708, 2731, 2755, 2778 };
unsigned char sin_amp = 100;
void EPWM_GPIO_Config(void)
{
	//--------------------------
	EALLOW;
	GpioCtrlRegs.GPAPUD.bit.GPIO0 = 0;    // Enable pull-up on GPIO0 (EPWM1A)
	GpioCtrlRegs.GPAPUD.bit.GPIO1 = 0;    // Enable pull-up on GPIO1 (EPWM1B)
	GpioCtrlRegs.GPAMUX1.bit.GPIO0 = 1;   // Configure GPIO0 as EPWM1A
	GpioCtrlRegs.GPAMUX1.bit.GPIO1 = 1;   // Configure GPIO1 as EPWM1B
#if 0
	GpioCtrlRegs.GPAPUD.bit.GPIO2 = 0;    // Enable pull-up on GPIO2 (EPWM2A)
	GpioCtrlRegs.GPAPUD.bit.GPIO3 = 0;    // Enable pull-up on GPIO3 (EPWM3B)
	GpioCtrlRegs.GPAMUX1.bit.GPIO2 = 1;   // Configure GPIO2 as EPWM2A
	GpioCtrlRegs.GPAMUX1.bit.GPIO3 = 1;   // Configure GPIO3 as EPWM2B

	GpioCtrlRegs.GPAPUD.bit.GPIO4 = 0;    // Enable pull-up on GPIO4 (EPWM3A)
	GpioCtrlRegs.GPAPUD.bit.GPIO5 = 0;    // Enable pull-up on GPIO5 (EPWM3B)
	GpioCtrlRegs.GPAMUX1.bit.GPIO4 = 1;   // Configure GPIO4 as EPWM3A
	GpioCtrlRegs.GPAMUX1.bit.GPIO5 = 1;   // Configure GPIO5 as EPWM3B
#endif
	//------------------TZ1引脚配置-----------------------
//	GpioCtrlRegs.GPAPUD.bit.GPIO12 = 0;    // Enable pull-up on GPIO12 (TZ1)
//	GpioCtrlRegs.GPAQSEL1.bit.GPIO12 = 3;  // Asynch input GPIO12 (TZ1)
//	GpioCtrlRegs.GPAMUX1.bit.GPIO12 = 1;  // Configure GPIO12 as TZ1
	EDIS;
}
/**************************************************
 * 函数名： void EPWM1_Config(void);
 * 输入参数:无；
 * 返回值:  无；
 * 调用：供外部函数调用
 * 备注：EPWM1用于驱动700V的移相全桥的A，B管；
 **************************************************/
void EPWM1_Config(void)
{
	EALLOW;
	SysCtrlRegs.PCLKCR1.bit.EPWM1ENCLK = 1;
	EDIS;
	EPwm1Regs.TBCTL.bit.CLKDIV = TB_CLKDIV1;
	EPwm1Regs.TBCTL.bit.HSPCLKDIV = TB_HSPCLKDIV1;
	EPwm1Regs.TBPRD = 20000; // 当前频率设置为10k
	EPwm1Regs.CMPA.half.CMPA = 4500; // Set 50% fixed duty for EPWM1A
	EPwm1Regs.TBPHS.half.TBPHS = 0; // Set Phase register to zero
	EPwm1Regs.TBCTL.bit.CTRMODE = TB_COUNT_UP; // Asymmetrical mode
	EPwm1Regs.TBCTL.bit.PHSEN = TB_DISABLE; // Master module
	EPwm1Regs.TBCTL.bit.PRDLD = TB_SHADOW;
	EPwm1Regs.TBCTL.bit.SYNCOSEL = TB_SYNC_DISABLE; // Sync down-stream module
	EPwm1Regs.CMPCTL.bit.SHDWAMODE = CC_SHADOW;
	EPwm1Regs.CMPCTL.bit.SHDWBMODE = CC_SHADOW;
	EPwm1Regs.CMPCTL.bit.LOADAMODE = CC_CTR_ZERO; // load on CTR=Zero
	EPwm1Regs.CMPCTL.bit.LOADBMODE = CC_CTR_ZERO; // load on CTR=Zero
	EPwm1Regs.AQCTLA.bit.ZRO = AQ_SET; // set actions for EPWM1A
	EPwm1Regs.AQCTLA.bit.CAU = AQ_CLEAR;
	EPwm1Regs.DBCTL.bit.OUT_MODE = DB_FULL_ENABLE; // enable Dead-band module
	EPwm1Regs.DBCTL.bit.POLSEL = DB_ACTV_HIC; // Active Hi complementary
	EPwm1Regs.DBFED = 500; // FED = 50 TBCLKs initially
	EPwm1Regs.DBRED = 500; // RED = 70 TBCLKs initially
//---------------------PWM使能ADC采样---------------------

	//EPWM1_IT_Config();
#if USE_TZ1
	EPwm1Regs.ETSEL.bit.SOCAEN = 1;        // Enable SOC on A group
	EPwm1Regs.ETSEL.bit.SOCASEL = 4;// Select SOC from from CPMA on upcount
	EPwm1Regs.ETPS.bit.SOCAPRD = 1;// Generate pulse on 1st event
	EALLOW;
	EPwm1Regs.TZSEL.bit.CBC1= TZ_ENABLE;
	EPwm1Regs.TZCTL.bit.TZA = TZ_FORCE_LO;
	EDIS;
#endif
}

/**************************************************
 * 函数名：void EPWM2_Config(void);
 * 输入参数:无;
 * 返回值：无；
 * 调用：供外部函数调用；
 * 备注：EPWM2用于驱动700V的移相全桥的C，D管；

 ***************************************************/
void EPWM2_Config(void)
{
	EALLOW;
	SysCtrlRegs.PCLKCR1.bit.EPWM2ENCLK = 1;
	EDIS;
	EPwm2Regs.TBCTL.bit.CLKDIV = TB_CLKDIV1;
	EPwm2Regs.TBCTL.bit.HSPCLKDIV = TB_HSPCLKDIV1;
	EPwm2Regs.TBPRD = 20000; // 当前频率设置为10k
	EPwm2Regs.CMPA.half.CMPA = 9500; // Set 50% fixed duty for EPWM1A
	EPwm2Regs.TBPHS.half.TBPHS = 0; // Set Phase register to zero
	EPwm2Regs.TBCTL.bit.CTRMODE = TB_COUNT_UP; // Asymmetrical mode
	EPwm2Regs.TBCTL.bit.PHSEN = TB_DISABLE; // Master module
	EPwm2Regs.TBCTL.bit.PRDLD = TB_SHADOW;
	EPwm2Regs.TBCTL.bit.SYNCOSEL = TB_SYNC_DISABLE; // Sync down-stream module
	EPwm2Regs.CMPCTL.bit.SHDWAMODE = CC_SHADOW;
	EPwm2Regs.CMPCTL.bit.SHDWBMODE = CC_SHADOW;
	EPwm2Regs.CMPCTL.bit.LOADAMODE = CC_CTR_ZERO; // load on CTR=Zero
	EPwm2Regs.CMPCTL.bit.LOADBMODE = CC_CTR_ZERO; // load on CTR=Zero
	EPwm2Regs.AQCTLA.bit.ZRO = AQ_SET; // set actions for EPWM1A
	EPwm2Regs.AQCTLA.bit.CAU = AQ_CLEAR;
	EPwm2Regs.DBCTL.bit.OUT_MODE = DB_FULL_ENABLE; // enable Dead-band module
	EPwm2Regs.DBCTL.bit.POLSEL = DB_ACTV_HIC; // Active Hi complementary
	EPwm2Regs.DBFED = 500; // FED = 50 TBCLKs initially
	EPwm2Regs.DBRED = 500; // RED = 70 TBCLKs initially
	/*----------以下代码是配置EPWM2模块响应外部错误事件,未使用--------*/
#if USE_TZ1
	EALLOW;
	EPwm2Regs.TZSEL.bit.CBC1= TZ_ENABLE;
	EPwm2Regs.TZCTL.bit.TZA = TZ_FORCE_LO;
	EDIS;
#endif
}
/**************************************************
 * 函数名:void EPWM3_Config(void);
 * 输入参数：无；
 * 返回值：无；
 * 调用：供外部函数调用;
 * 备注：EPWM3用于驱动200V的移相全桥A,B管；
 ***************************************************/
void EPWM3_Config(void)
{
	EALLOW;
	SysCtrlRegs.PCLKCR1.bit.EPWM3ENCLK = 1;
	EDIS;
	EPwm3Regs.TBCTL.bit.CLKDIV = TB_CLKDIV1;
	EPwm3Regs.TBCTL.bit.HSPCLKDIV = TB_HSPCLKDIV1;
	EPwm3Regs.TBPRD = 20000; // 当前频率设置为10k
	EPwm3Regs.CMPA.half.CMPA = 9500; // Set 50% fixed duty for EPWM1A
	EPwm3Regs.TBPHS.half.TBPHS = 0; // Set Phase register to zero
	EPwm3Regs.TBCTL.bit.CTRMODE = TB_COUNT_UP; // Asymmetrical mode
	EPwm3Regs.TBCTL.bit.PHSEN = TB_DISABLE; // Master module
	EPwm3Regs.TBCTL.bit.PRDLD = TB_SHADOW;
	EPwm3Regs.TBCTL.bit.SYNCOSEL = TB_SYNC_DISABLE; // Sync down-stream module
	EPwm3Regs.CMPCTL.bit.SHDWAMODE = CC_SHADOW;
	EPwm3Regs.CMPCTL.bit.SHDWBMODE = CC_SHADOW;
	EPwm3Regs.CMPCTL.bit.LOADAMODE = CC_CTR_ZERO; // load on CTR=Zero
	EPwm3Regs.CMPCTL.bit.LOADBMODE = CC_CTR_ZERO; // load on CTR=Zero
	EPwm3Regs.AQCTLA.bit.ZRO = AQ_SET; // set actions for EPWM1A
	EPwm3Regs.AQCTLA.bit.CAU = AQ_CLEAR;
	EPwm3Regs.DBCTL.bit.OUT_MODE = DB_FULL_ENABLE; // enable Dead-band module
	EPwm3Regs.DBCTL.bit.POLSEL = DB_ACTV_HIC; // Active Hi complementary
	EPwm3Regs.DBFED = 500; // FED = 50 TBCLKs initially
	EPwm3Regs.DBRED = 500; // RED = 70 TBCLKs initially
	/*------------以下代码是对外部错误信号进行相应，目前是不用配置------------*/
#if USE_TZ1
	EALLOW;
	EPwm3Regs.TZSEL.bit.CBC1= TZ_ENABLE;
	EPwm3Regs.TZCTL.bit.TZA = TZ_FORCE_LO;
	EDIS;
#endif
}
void EPWM_set(u16 epwm1, u16 epwm2, u16 epwm3)
{
	EPwm1Regs.CMPA.half.CMPA = epwm1;
	EPwm2Regs.CMPA.half.CMPA = epwm2;
	EPwm3Regs.CMPA.half.CMPA = epwm3;
}
void EPWM1_IT_Config(void)
{
	EPwm1Regs.ETCLR.bit.INT = 1;
	EPwm1Regs.ETSEL.bit.INTEN = 1;
	EPwm1Regs.ETSEL.bit.INTSEL = ET_CTR_ZERO;
	EPwm1Regs.ETPS.bit.INTPRD = ET_1ST;
}
unsigned short int epwm1A_sin_cnt = 0, epwm1b_sincnt = 119;
__interrupt void EPWM1_isr(void)
{
	if (EPwm1Regs.ETFLG.bit.INT == 1)
	{
		//EPwm1Regs.CMPA.half.CMPA =3816;
		//EPwm2Regs.CMPA.half.CMPA =3816;
	//	EPwm3Regs.CMPA.half.CMPA =3816;

		epwm1A_sin_cnt++;
		if (epwm1A_sin_cnt == table_size)
		{
			epwm1A_sin_cnt = 0;
		}
	//	EPwm1Regs.CMPB = (u16) sin_tabele[epwm1b_sincnt];
		epwm1b_sincnt++;
		if (epwm1b_sincnt == table_size)
		{
			epwm1b_sincnt = 0;
		}
		EPwm1Regs.ETCLR.bit.INT = 1;
	}
	PieCtrlRegs.PIEACK.bit.ACK3 = 1;
}

