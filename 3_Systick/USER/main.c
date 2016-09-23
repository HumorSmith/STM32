#include "stm32f10x.h"
#include "led.h"
#include "stm32f10x_rcc.h"
#include "misc.h"
#include <stdio.h>
#include "usart.h"
static __IO uint32_t TimingDelay=0;  

void TimingDelay_Decrement(void)    
{    
	  if (TimingDelay != 0x00)    
	  {     
	    TimingDelay--;    
	  }  
}   

void Delay(uint32_t times){
   TimingDelay = times;  
   while (TimingDelay != 0) ; 
}

void RCC_Config(void)  
{  
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB |  
                           RCC_APB2Periph_GPIOC | RCC_APB2Periph_GPIOD |  
                           RCC_APB2Periph_GPIOE | RCC_APB2Periph_GPIOF |  
                           RCC_APB2Periph_GPIOG, ENABLE);  
  
} 

/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None
  */
void SysTick_Handler(void)
{
	// printf("SysTick_Handler");
	 TimingDelay--;  
}


void Delay(__IO u32 nCount);
void NVIC_Configuration(void);
int main(){
	RCC_Config();
	LED_GPIO_Config();
  USART1_Config();
	if (SysTick_Config(72000)) //SysTick_Config: return 0->success 1->failure  
  {  
			while(1);
  } 
	while(1){
		LED1(ON);
		Delay(1000);
		printf("LED1(ON)");
		LED1(OFF);
		Delay(1000);
		printf("LED1(OFF)");
	}
}
