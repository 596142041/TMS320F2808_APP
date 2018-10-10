/********************************************************
 *文件名:pid.c
 *创建时间:2018-10-09
 *作者: 皇甫仁和
 ********************************************************/
#include "pid.h"
void PIDInit(PID *pid)
{
	pid->LastError  = 0;			//Error[-1]
	pid->PrevError  = 0;			//Error[-2]
	pid->Proportion = 0.0;			//比例常数 Proportional Const
	pid->Integral   = 0.0;			//积分常数 Integral Const
	pid->Derivative = 0;			//微分常数 Derivative Const
	pid->SetPoint   = 0.0;		//设定值
	pid->SumError   = 0;			//累计误差
}
void PIDSetPoint(PID *pid,float setpoint)
{
	pid->SetPoint = setpoint;
}
float PIDGetSetpoint(PID *pid)
{
	return pid->SetPoint;
}
//设置PID的相关系数
void PIDSetKp(PID *pid,float dKpp)
{
	pid->Proportion = dKpp;
}
float PIDGetKp(PID *pid)
{
	return pid->Proportion;
}

void PIDSetKi(PID *pid,float dKii)
{
	pid->Integral = dKii;
}
float PIDGetKi(PID *pid)
{
	return pid->Integral;
}

void PIDSetKd(PID *pid,float dKdd)
{
	pid->Derivative = dKdd;
}
float PIDGetKd(PID *pid)
{
	return pid->Derivative;
}
//增量式PID
 int IncPIDCalc(PID *pid,float NextPoint)
 {
	volatile int incPID;
	float error;
	error = pid->SetPoint-NextPoint;
	incPID = (int)(pid->Proportion*error-pid->Integral*pid->LastError+pid->Derivative*pid->PrevError);
	pid->PrevError = pid->LastError;
	pid->LastError =error;
	return incPID;
 }

