#include "led.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_gpio.h"
void LED_GPIO_Config(void){
	//声明一个GPIO的结构体
	GPIO_InitTypeDef GPIO_InitStructure;
	//开启GPIOA外设时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	//设置操作的为PA2
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
	//设置开漏输出
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	//速度50赫兹
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	//初始化
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	//给一个PA2一个高电平
	GPIO_SetBits(GPIOA,GPIO_Pin_2);
}