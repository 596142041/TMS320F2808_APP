/********************************************************
 *文件名:EPWM.h
 *创建时间:2018-10-09
 *作者: 皇甫仁和
 ********************************************************/
#ifndef TMS320F2808_USER_INC_EPWM_H_
#define TMS320F2808_USER_INC_EPWM_H_
#include "include.h"
#define USE_TZ1 0
void EPWM_GPIO_Config(void);
void EPWM1_Config(void);
void EPWM2_Config(void);
void EPWM3_Config(void);
void EPWM1_IT_Config(void);
void EPWM_set(u16 epwm1,u16 epwm2,u16 epwm3);
__interrupt void EPWM1_isr(void);
#endif /* TMS320F2808_USER_INC_EPWM_H_ */
