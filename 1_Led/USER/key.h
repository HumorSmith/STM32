#ifndef __KEY_H
#define __KEY_H
#include "stm32f10x.h"
#define KEY_ON 0
#define KEY_OFF 1
#define KEY0  GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_4) //PE4按钮监听
void KEY_GPIO_Config(void);	
#endif										