#include "stm32f10x.h"
#include "led.h"
#include "stm32f10x_rcc.h"
#include "misc.h"
#include <stdio.h>
//延时函数
void Delay(uint32_t nCount){
	uint32_t i,j;
	{
		for(i=0;i<nCount;i++);
	}
	
}
int main(){
 	LED_GPIO_Config();

	while(1){
		LED1(ON);
		Delay(0xFFFFF);
		//关闭LED
		LED1(OFF);
		Delay(0xFFFFF);
	}
}





