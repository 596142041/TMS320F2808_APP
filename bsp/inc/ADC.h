/********************************************************
 *文件名:ADC.h
 *创建时间:2018-10-09
 *作者: 皇甫仁和
 ********************************************************/
#ifndef TMS320F2808_USER_INC_ADC_H_
#define TMS320F2808_USER_INC_ADC_H_
#include "include.h"
#define ADC_CH_Num   12
#define ADC_filter   13
typedef struct _ADC_Register
{
	u16 Reg_NTC;
	u16 Reg_PTC;
	u16 Reg_OC_REF;
	u16 Reg_5V;
	u16 Reg_24V;
	u16 Reg_UDC;
	u16 Reg_IDC;
	u16 Reg_AI1;
	u16 Reg_AI2;
	u16 Reg_AI3;
	u16 Reg_TEMP_U;
	u16 Reg_TEMP_V;
	u16 Reg_TEMP_W;
	u16 Reg_IU;
	u16 Reg_IV;
	u16 Reg_IW;
}ADC_Register;
typedef union _ADC_register
{
	u16 all[16];
	ADC_Register REG;
}ADC_register;

typedef struct  _Sampling_Value
{
	float Sampl_Value_NTC;
	float Sampl_Value_PTC;
	float Sampl_Value_OC_REF;
	float Sampl_Value_5V;
	float Sampl_Value_24V;
	float Sampl_Value_UDC;
	float Sampl_Value_IDC;
	float Sampl_Value_AI1;
	float Sampl_Value_AI2;
	float Sampl_Value_AI3;
	float Sampl_Value_TEMP_U;
	float Sampl_Value_TEMP_V;
	float Sampl_Value_TEMP_W;
	float Sampl_Value_IU;
	float Sampl_Value_IV;
	float Sampl_Value_IW;
}Sampling_Value;
typedef struct _Real_value
{
    float real_Value_NTC;
    float real_Value_PTC;
    float real_Value_OC_REF;
    float real_Value_5V;
    float real_Value_24V;
    float real_Value_UDC;
    float real_Value_IDC;
    float real_Value_AI1;
    float real_Value_AI2;
    float real_Value_AI3;
    float real_Value_TEMP_U;
    float real_Value_TEMP_V;
    float real_Value_TEMP_W;
    float real_Value_IU;
    float real_Value_IV;
    float real_Value_IW;
}Real_value;
typedef union _Sampling_value
{
	float32 all[16];
	Sampling_Value sample_value;
}Sampling_value;
void Init_ADC_Value(void);
void ADC_Config(void);
void ADC_readdata(ADC_Register *Reg);
void ADC_Calc(Sampling_Value *sample,ADC_Register *Reg);
__interrupt void ADC_isr(void);
void ADC_v_Data(unsigned short int *data,unsigned short int temp);
float ADC_v_data(unsigned short int *adc_data,unsigned short int temp);
extern Sampling_value sample_value;
extern ADC_register ADC_ValueReg;
extern u16 Reg_24V_temp[ADC_filter], Reg_5V_temp[ADC_filter],  Reg_OCREF_temp[ADC_filter];
extern u16 Reg_IW_temp[ADC_filter],  Reg_IV_temp[ADC_filter],  Reg_IU_temp[ADC_filter];
extern u16 Reg_PTC_temp[ADC_filter], Reg_NTC_temp[ADC_filter], Reg_AI3_temp[ADC_filter];
#endif /* TMS320F2808_USER_INC_ADC_H_ */
