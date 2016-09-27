#include "stm32f10x.h"
#include "led.h"
#include "stm32f10x_rcc.h"
#include "misc.h"
#include "usart.h"
#include <stdio.h>
#include "stm32f10x_dma.h"
extern uint8_t SendBuff[SENDBUFF_SIZE];
void Delay(uint32_t nCount){
  uint32_t i;
  for(i=0;i<nCount;i++);
}

int main(){
  uint32_t i;
  LED_GPIO_Config();
  USART1_Config();
  DMA_Config();
	/*开始数据填充*/
  for(i=0;i<SENDBUFF_SIZE;i++)
  {
		SendBuff[i]	 = 0xff;
  }
	USART_DMACmd(USART1,USART_DMAReq_Tx,ENABLE);
	LED1(ON);
	while(1);
}
