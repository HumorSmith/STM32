#ifndef _USAR_H_
#define _USAR_H_
#include "stm32f10x.h"
#include "stm32f10x_usart.h"
#include "stm32f10x_dma.h"
#define USART1_DR_Base  0x40013804
#define SENDBUFF_SIZE 5000
void DMA_Config(void);
void USART1_Config(void);  
void NVIC_Config(void);
#endif
