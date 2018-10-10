/********************************************************
 *文件名:RDC.c
 *创建时间:2018-10-09
 *作者: 皇甫仁和
 ********************************************************/
#ifndef USER_INC_RDC_H_
#define USER_INC_RDC_H_
#include "include.h"
typedef union
{
	u16 all;
	struct
	{
		u16 PAR:1;
		u16 LOT:1;
		u16 DOS:1;
		u16 RDVEL:1;
		u16 data:12;
	}bit;
}RDC_DATA;
void RDC_GPIO_Config(void);
void RDC_SPI_Config(void);
void Read_RDC_data(RDC_DATA *data);
extern RDC_DATA RDC_data;
#endif /* USER_INC_RDC_H_ */
