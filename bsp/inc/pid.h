/********************************************************
 *文件名:pid.h
 *创建时间:2018-10-09
 *作者: 皇甫仁和
 ********************************************************/
#ifndef USER_INC_PID_H_
#define USER_INC_PID_H_
typedef struct PID
{
	float  SetPoint; 			//  设定目标 Desired Value
	float  SumError;			           //	误差累计
	float  Proportion;                     //  比例常数 Proportional Const
	float  Integral;                       //  积分常数 Integral Const
	float  Derivative;                     //  微分常数 Derivative Const
	float LastError;         	           //  最后一次的误差
	float PrevError;                       // 倒数第二次的误差
	//对输出进行限幅
	unsigned short int MAX_output;
	unsigned short int MIN_output;
} PID;
void PIDInit(PID *pid);
void PIDSetErrorSum(PID *pid,float ErrorSum);
void PIDSetPoint(PID *pid,float setpoint);
float PIDGetSetpoint(PID *pid);
//设置PID的相关系数
void PIDSetKp(PID *pid,float dKpp);
float PIDGetKp(PID *pid);

void PIDSetKi(PID *pid,float dKii);
float PIDGetKi(PID *pid);

void PIDSetKd(PID *pid,float dKdd);
float PIDGetKd(PID *pid);
//增量式PID
 int IncPIDCalc(PID *pid,float NextPoint);
//位置式PID
unsigned int LocPIDCalc(PID *pid,unsigned short int NextPoint);


#endif /* USER_INC_PID_H_ */
