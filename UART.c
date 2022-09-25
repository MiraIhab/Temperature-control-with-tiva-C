#include "UART.h"
void InitUART(){
	// UART0
	SYSCTL_RCGCGPIO_R |= 0x01U;
	SYSCTL_RCGCUART_R |= 0x01U; 
	while(SYSCTL_PRGPIO_R & 0x01U == 0x00){}
	UART0_CTL_R &= ~0x001;
	UART0_IBRD_R = 312;
	UART0_FBRD_R = 11;
	UART0_CC_R = 0;
	UART0_LCRH_R = 0x060;
	UART0_CTL_R = 0x0301;
		
	GPIO_PORTA_AFSEL_R |= 0x03;
	GPIO_PORTA_PCTL_R = (GPIO_PORTA_PCTL_R & 0XFFFFFF00) + 0X011;
	GPIO_PORTA_DEN_R |= 0x03;
	GPIO_PORTA_AMSEL_R &= ~0x03;
	
	GPIO_PORTF_IS_R &= ~0x10;
	GPIO_PORTF_IBE_R &= ~0x10;
	GPIO_PORTF_IEV_R &= ~0x10;
	GPIO_PORTF_ICR_R |= 0x10;
	GPIO_PORTF_IM_R |= 0x10;
	
	NVIC_PRI7_R = 7<<21;
	NVIC_EN0_R |= 1 <<30;
	
	vTaskSuspend(NULL);
}
void UART0_Transmitter(char data)  
{
    while((	UART0_FR_R& 0x20) != 0); 
    UART0_DR_R = data;                 
}
char UART0_Receiver(void)  
{
    char data;
	  while((UART0->FR & (1<<4)) != 0); /* wait until Rx buffer is not full */
    data = UART0->DR ;  	/* before giving it another byte */
    return (unsigned char) data; 
}
