#include "stm32f10x.h"
#include "led.h"
#include "stm32f10x_rcc.h"
#include "misc.h"
#include "tim.h"
#include <stdio.h>
#include "usart.h"
#include "delay.h"
volatile u32 time; // 计时变量

int main(){
 	LED_GPIO_Config();
	USART1_Config();
	//配置Tim2
	TIM2_NVIC_Configuration();
  TIM2_Configuration();
	START_TIME;
	printf("main");
	while(1){
		LED1(ON);
		Delay(0xFFFFF);
	}
}





