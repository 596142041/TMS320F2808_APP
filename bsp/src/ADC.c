/********************************************************
 *文件名:ADC.c
 *创建时间:2018-10-09
 *作者: 皇甫仁和
 ********************************************************/
#include "ADC.h"
u16 Reg_24V_temp[ADC_filter], Reg_5V_temp[ADC_filter],  Reg_OCREF_temp[ADC_filter];
u16 Reg_IW_temp[ADC_filter],  Reg_IV_temp[ADC_filter],  Reg_IU_temp[ADC_filter];
u16 Reg_PTC_temp[ADC_filter], Reg_NTC_temp[ADC_filter];
u16 Reg_AI1_temp[ADC_filter],Reg_AI2_temp[ADC_filter], Reg_AI3_temp[ADC_filter];
u16 IGBT_U_temp[ADC_filter];
ADC_register ADC_ValueReg;
Sampling_value sample_value;
extern Sys_Register sys_reg;
void ADC_Config(void)
{
	EALLOW;
	 SysCtrlRegs.PCLKCR0.bit.ADCENCLK = 1;    // ADC
	EDIS;

	InitAdc();  // For this example, init the ADC
	/*---------目前根据数据手册来配置相关寄存器------*/
	AdcRegs.ADCTRL1.bit.SUSMOD = 0x00;//表示在仿真挂起是，忽略，继续转换;
	AdcRegs.ADCTRL1.bit.ACQ_PS = 0x0f;//采样窗口的大小，
	AdcRegs.ADCTRL1.bit.CPS = 0x00;//确定ADC的工作时钟频率
	AdcRegs.ADCTRL1.bit.SEQ_OVRD = 1;//目前不是太明白
	AdcRegs.ADCTRL1.bit.SEQ_CASC = 1;//配置成为级联模式;
	/*-----------以下是配置控制寄存器2----------*/
	AdcRegs.ADCTRL2.bit.EPWM_SOCA_SEQ1 = 0;// Enable SOCA from ePWM to start SEQ1
	AdcRegs.ADCTRL2.bit.INT_ENA_SEQ1 = 0;  // Enable SEQ1 interrupt (every EOS)
	/*-------------------END---------------------*/
	/*-----------------以下配置是ADC控制寄存器3----------------*/
	AdcRegs.ADCTRL3.bit.ADCCLKPS = 10;//固ADC时钟频率为150MHz/(8*2);
	AdcRegs.ADCTRL3.bit.SMODE_SEL = 0;//顺序采样
	//现在是采用的是级联模式，同时还是顺序采样模式
	AdcRegs.ADCMAXCONV.bit.MAX_CONV1 = 11-1;//采样通道数:是MAX_CONV+1;即采样通道数为2通道

	AdcRegs.ADCCHSELSEQ1.bit.CONV00 = 0x0B;//IW
	AdcRegs.ADCCHSELSEQ1.bit.CONV01 = 0x0C;//IV
	AdcRegs.ADCCHSELSEQ1.bit.CONV02 = 0x0D;//IU

	AdcRegs.ADCCHSELSEQ1.bit.CONV03 = 0x06;//OC_REF
	AdcRegs.ADCCHSELSEQ2.bit.CONV04 = 0x05;//5V
	AdcRegs.ADCCHSELSEQ2.bit.CONV05 = 0x0A;//24V

	AdcRegs.ADCCHSELSEQ2.bit.CONV06 = 0x0F;//PTC
	AdcRegs.ADCCHSELSEQ2.bit.CONV07 = 0x07;//NTC

	AdcRegs.ADCCHSELSEQ3.bit.CONV08 = 0x01;//AI3
	AdcRegs.ADCCHSELSEQ3.bit.CONV09 = 0x03;//AI3
	AdcRegs.ADCCHSELSEQ3.bit.CONV10 = 0x02;//AI2
	AdcRegs.ADCTRL1.bit.CONT_RUN = 1;//配置ADC的工作方式，工作于连续采样模式
	AdcRegs.ADCTRL2.bit.SOC_SEQ1 = 1;
}
void ADC_readdata(ADC_Register *Reg)
{
	Reg->Reg_IW     = AdcRegs.ADCRESULT0>>4;//IW
	Reg->Reg_IV     = AdcRegs.ADCRESULT1>>4;//
	Reg->Reg_IU     = AdcRegs.ADCRESULT2>>4;//

	Reg->Reg_OC_REF = AdcRegs.ADCRESULT3>>4;//
	Reg->Reg_5V     = AdcRegs.ADCRESULT4>>4;//
	Reg->Reg_24V    = AdcRegs.ADCRESULT5>>4;//

	Reg->Reg_PTC    = AdcRegs.ADCRESULT6>>4;//
	Reg->Reg_NTC    = AdcRegs.ADCRESULT7>>4;//

	Reg->Reg_AI3    = AdcRegs.ADCRESULT8>>4;//
	Reg->Reg_AI1    = AdcRegs.ADCRESULT9>>4;//
	Reg->Reg_AI2    = AdcRegs.ADCRESULT10>>4;//
}
void ADC_v_Data(unsigned short int *data,unsigned short int temp)
{
#if 0
    data[12] = data[11];
    data[11] = data[10];
    data[10] = data[9];
    data[9] = data[8];
	data[8] = data[7];
	data[7] = data[6];
	data[6] = data[5];
	data[5] = data[4];
	data[4] = data[3];
	data[3] = data[2];
	data[2] = data[1];
	data[1] = data[0];
#endif
	int i = 0;
	for(i=0;i<ADC_filter-1;i++)
	{
	    data[i+1] = data[i];
	}
	data[0] = temp;
}
float ADC_v_data(unsigned short int *adc_data,unsigned short int temp)
{
    char i,j;
    unsigned short int a[ADC_filter];
    unsigned short int  t;
    float data;
    ADC_v_Data(adc_data,temp);
    for(i = 0; i < ADC_filter; i++)
    {
        a[i] = adc_data[i];
    }
    for(i=0; i<ADC_filter-1; i++)
    {
        for(j=0; j<ADC_filter-1-i; j++)
		if(a[j]>a[j+1])
		{
			t=a[j];
			a[j]=a[j+1];
			a[j+1]=t;
		}
    }
    for(i = 2;i<ADC_filter-3;i++)
    {
        data = (float)((a[i])+data);
    }

    data = data*3000/(float)(4095*9.0);
    return data;
}
void ADC_Calc(Sampling_Value *sample,ADC_Register *Reg)
{
	ADC_readdata(Reg);
	sample->Sampl_Value_24V     =   ADC_v_data(Reg_24V_temp,Reg->Reg_24V);
	sample->Sampl_Value_5V      =   ADC_v_data(Reg_5V_temp,Reg->Reg_5V);
	sample->Sampl_Value_OC_REF  =	ADC_v_data(Reg_OCREF_temp,Reg->Reg_OC_REF);
	sample->Sampl_Value_AI3     =	ADC_v_data(Reg_AI3_temp,Reg->Reg_AI3);
	sample->Sampl_Value_AI1     =   ADC_v_data(Reg_AI1_temp,Reg->Reg_AI1);
	sample->Sampl_Value_AI2     =   ADC_v_data(Reg_AI2_temp,Reg->Reg_AI2);
	sample->Sampl_Value_IU      =	ADC_v_data(Reg_IU_temp,Reg->Reg_IU);
	sample->Sampl_Value_IV      = 	ADC_v_data(Reg_IV_temp,Reg->Reg_IV);
	sample->Sampl_Value_IW      =	ADC_v_data(Reg_IW_temp,Reg->Reg_IW);
	sample->Sampl_Value_PTC     =	ADC_v_data(Reg_PTC_temp,Reg->Reg_PTC);
	sample->Sampl_Value_NTC     =	ADC_v_data(Reg_NTC_temp,Reg->Reg_NTC);
}
__interrupt void ADC_isr(void)
{
	if(AdcRegs.ADCST.bit.INT_SEQ1 == 1)
	{
	  //  ADC_Calc(&sample_value.sample_value,&ADC_ValueReg.REG);
		//sys_reg.ADC_sample_cnt++;
	//	if(sys_reg.ADC_sample_cnt %1000 == 0)
		{
		//	sys_reg.ADC_sample_cnt = 0;
		}
		AdcRegs.ADCST.bit.INT_SEQ1_CLR = 1;

		  AdcRegs.ADCTRL2.bit.RST_SEQ1 = 1;         // Reset SEQ1
	}
	PieCtrlRegs.PIEACK.bit.ACK1 = 1;   // Acknowledge interrupt to PIE
}
