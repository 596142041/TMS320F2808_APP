/**********************************************
 * Double_pulse.h
 * Created on: 2019年1月16日
 * Author: admin
 * Version:
 ************************************************/

#ifndef BSP_INC_DOUBLE_PULSE_H_
#define BSP_INC_DOUBLE_PULSE_H_
#include "include.h"
typedef enum _state
{
    Stop      = 0,
    Signal    = 1,
    Double    = 2,
    Continue  = 3,
}Double_pulse_Mode;
void Double_pulse_GPIO_init(void);
void Double_pulse_run(Double_pulse_Mode mode,u8 channel,u16 t1,u16 t2, u16 t3);




#endif /* BSP_INC_DOUBLE_PULSE_H_ */
