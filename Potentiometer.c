#include "Potentiometer.h"

void ADC_init(void){
	
    /* Enable Clock to ADC0 and GPIO pins*/
    SYSCTL->RCGCGPIO |= (1<<4);   /* Enable Clock to GPIOE or PE3/AN0 */
	  delayMs(10);									/* 10 msec delay to enable the clock */
    SYSCTL->RCGCADC |= (1<<0);    /* ADC0 clock enable*/
    
    /* initialize PE3 for AN0 input  */
    GPIOE->AFSEL |= (1<<3);       /* enable alternate function */
    GPIOE->DEN &= ~(1<<3);        /* disable digital function */
    GPIOE->AMSEL |= (1<<3);       /* enable analog function */
   
    /* initialize sample sequencer3 */
    ADC0->ACTSS &= ~(1<<3);        				/* disable SS3 during configuration */
    ADC0->EMUX &= ~0xF000;    						/* software trigger conversion */
    ADC0->SSMUX3 = 0;         	 					/* get input from channel 0 */
    ADC0->SSCTL3 |= (1<<1)|(1<<2);        /* take one sample at a time, set flag at 1st sample */
    ADC0->ACTSS |= (1<<3);         				/* enable ADC0 sequencer 3 */
    
	  /*Iniitialize PF3 as a digital output pin */
		SYSCTL->RCGCGPIO |= 0x20;  /* turn on bus clock for GPIOF */
		delayMs(10);							 /* 10 msec delay to enable the clock */
		GPIOF->DIR       |= 0x1F;  /* set GREEN pin as a digital output pin */
		GPIOF->DEN       |= 0x1F; 		/* Enable PF3 pin as a digital pin */ 
		GPIOF->CR       |= 0x1F;
		GPIOF->PUR       |= 0x11;
}

