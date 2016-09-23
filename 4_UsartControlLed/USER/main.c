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
char ReceivedData = NULL;
int main(){
	LED_GPIO_Config();
  USART1_Config();
	while(1){
		 /* Wait until a byte is received */
   while(USART_GetFlagStatus(USART1, USART_FLAG_RXNE) == RESET)
    {
    }
    /* read byte and print via usart2 it */
    ReceivedData = USART_ReceiveData(USART1);
    printf("Positionen: %d \r\n", ReceivedData);     
		if (ReceivedData == '1'){
			printf("LED1(ON)");
			LED1(ON);
			Delay(0xFFFFFF);	
		}else if(ReceivedData=='0'){
			LED1(OFF);
			Delay(0xFFFFFF);
			printf("LED1(OFF)");
		}else{
			break;
		}
	
	}
}
