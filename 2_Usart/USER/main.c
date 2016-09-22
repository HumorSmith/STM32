#include "stm32f10x.h"
#include "led.h"
#include "stm32f10x_rcc.h"
#include "misc.h"
#include "usart.h"
#include <stdio.h>
void Delay(uint32_t nCount){
	uint32_t i;
  for(i=0;i<nCount;i++);
}

int main(){
	LED_GPIO_Config();
  USART1_Config();
	while(1){
		LED1(ON);
		Delay(0xFFFFFF);
		LED1(OFF);
		Delay(0xFFFFFF);
		printf("2");
	}
}
