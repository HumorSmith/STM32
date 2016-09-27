#include "usart.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "stm32f10x_dma.h"
#include "misc.h"
#include "stm32f10x_rcc.h"
uint8_t SendBuff[SENDBUFF_SIZE];
void USART1_Config(void)  
{  
    /* USART configuration structure for USART1 */
    USART_InitTypeDef usart1_init_struct;
    /* Bit configuration structure for GPIOA PIN9 and PIN10 */
    GPIO_InitTypeDef gpioa_init_struct;
     
    /* Enalbe clock for USART1, AFIO and GPIOA */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1 | RCC_APB2Periph_AFIO | 
                           RCC_APB2Periph_GPIOA, ENABLE);
                            
    /* GPIOA PIN9 alternative function Tx */
    gpioa_init_struct.GPIO_Pin = GPIO_Pin_9;
    gpioa_init_struct.GPIO_Speed = GPIO_Speed_50MHz;
    gpioa_init_struct.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_Init(GPIOA, &gpioa_init_struct);
    /* GPIOA PIN9 alternative function Rx */
    gpioa_init_struct.GPIO_Pin = GPIO_Pin_10;
    gpioa_init_struct.GPIO_Speed = GPIO_Speed_50MHz;
    gpioa_init_struct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOA, &gpioa_init_struct);
 
    /* Enable USART1 */
    USART_Cmd(USART1, ENABLE);  
    /* Baud rate 9600, 8-bit data, One stop bit
     * No parity, Do both Rx and Tx, No HW flow control
     */
    usart1_init_struct.USART_BaudRate = 115200;   
    usart1_init_struct.USART_WordLength = USART_WordLength_8b;  
    usart1_init_struct.USART_StopBits = USART_StopBits_1;   
    usart1_init_struct.USART_Parity = USART_Parity_No ;
    usart1_init_struct.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
    usart1_init_struct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    /* Configure USART1 */
    USART_Init(USART1, &usart1_init_struct);
    /* Enable RXNE interrupt */
    //USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
    /* Enable USART1 global interrupt */
}

static void NVIC_Config(void)
{
  NVIC_InitTypeDef NVIC_InitStructure;
  
  /* Configure one bit for preemption priority */
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
  
  /* 配置P[A|B|C|D|E]为中断源 */
  NVIC_InitStructure.NVIC_IRQChannel = DMA1_Channel4_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
}


void DMA_Config(void)
{
    DMA_InitTypeDef DMA_InitStructure;

	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);	//开启DMA时钟
	NVIC_Config();	   			//配置DMA

    /*设置DMA源:内存地址&串口数据寄存器地址*/
  DMA_InitStructure.DMA_PeripheralBaseAddr = USART1_DR_Base;	   

	/*内存地址(要传输变量的指针)*/  
    DMA_InitStructure.DMA_MemoryBaseAddr = (u32)SendBuff;
	
	/*方向：从内存到外设*/
    DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralDST;	
	
	/*传输大小DMA_BufferSize=SENDBUFF_SIZE*/	
    DMA_InitStructure.DMA_BufferSize = SENDBUFF_SIZE;
	
	/*外设地址不增*/	    
    DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable; 
	
	/*内存地址自增*/
    DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;	
	
	/*内存数据单元*/	
    DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
	
	/*外设数据单位*/
    DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;	 
	
   /*DMA模式，一次传输，循环*/
    DMA_InitStructure.DMA_Mode = DMA_Mode_Normal ;	 
	
	/*优先级中*/	
    DMA_InitStructure.DMA_Priority = DMA_Priority_Medium;  
	
	/*禁止内存到内存的传输	*/
    DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
	
	/*配置DMA1的4通道*/		   
    DMA_Init(DMA1_Channel4, &DMA_InitStructure); 	   
	
		DMA_Cmd (DMA1_Channel4,ENABLE);					//使能DMA
		DMA_ITConfig(DMA1_Channel4,DMA_IT_TC,ENABLE);  //配置DMA发送完成后产生中断

}


int fputc(int ch, FILE *f)  
{  
	USART_SendData(USART1,ch);  
  while(USART_GetFlagStatus(USART1,USART_FLAG_TC)==RESET);  
  return(ch);  
}  
  
  
int fgetc(FILE *f)  
{  
  while (USART_GetFlagStatus(USART1, USART_FLAG_RXNE) == RESET);  
  
  return (int)USART_ReceiveData(USART1);  
} 

