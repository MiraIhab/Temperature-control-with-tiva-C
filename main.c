
#include <stdint.h>
#include <FreeRTOS.h>
#include "tm4c123gh6pm.h"
#include "task.h"
#include "LCD.h"
#include "UART.h"
#include "Potentiometer.h".
#include "ITOA.h"
#include "queue.h"
#include "system_TM4C123.h"
#include "semphr.h"
#include "TM4C123GH6PM.h"
#include "TM4C123.h"    // Device header
  														  

QueueHandle_t xUARTQueue;
QueueHandle_t xLCDQueue;
QueueHandle_t xBuzzerQueue;
void Task1(void *pvParameters){
	
	char *cpy;
	char *on;
	char off=0;
		unsigned int temperature;
unsigned int adc_value;    //variable that contains adc value 
float mV;
unsigned int setpoint;
	typedef struct Message {
		char Txt1[4];
		char Txt2[4];
	} AMessage;
	AMessage msg;

	 while(1)
    {   
        xQueueReceive(xUARTQueue,&setpoint,0);// recieve setpoint value from queue
        ADC0->PSSI |= (1<<3);        		/* Enable SS3 conversion or start sampling data from AN0 */
        while((ADC0->RIS & 8) == 0) ;   /* Wait untill sample conversion completed*/
        adc_value = ADC0->SSFIFO3; 			/* read adc coversion result from SS3 FIFO*/
			  // mapping input value from potentiometer to temperature
			  mV = adc_value*3300/4096;
			  mV= (mV-500.0)/10.0;
			  temperature =(float)mV; 
			 myitoa(temperature,msg.Txt1,10);
			 myitoa(setpoint,msg.Txt2,10);
			 xQueueSend(xLCDQueue,&msg,0);// send setpoint and measured temperature to LCD queue
        ADC0->ISC = 8;          				/* clear coversion clear flag bit*/
 				/* control Green PF3->LED */
				if(temperature > setpoint)
					GPIOF->DATA  = 0x02; /* turn on red LED*/
				else if(temperature< setpoint)
					GPIOF->DATA  = 0x04; /* turn on blue LED*/
				else if(temperature== setpoint)
					GPIOF->DATA  = 0x08; /* turn on green LED*/
              
	
    }
	}
void Task2(){
	unsigned N;
	unsigned AdcValue;
	unsigned char Total;
	InitUART();
	while (1){
// print enter set point
char *intro = "Enter Temperature Setpoint (Degrees): ";
for(int i = 0; i < 35; i++){
				UART0_Transmitter(intro[i]);
			}
	UART0_Transmitter('\n');
	UART0_Transmitter('\r');

 N=0;
 Total=0;
	while (1){
// recieve setpoint value entered by user
		N=UART0_Receiver();
		UART0_Transmitter(N);
		if(N=='\r')break;
		N=N-'0';
		Total=Total*10+N;
	}
char *change = " Temperature setpoint changed .. ";
for(int i = 0; i < 24 ; i++){
				UART0_Transmitter(change[i]);
			}
	UART0_Transmitter('\n');
	UART0_Transmitter('\r');
// send set point value to queue
	xQueueSend(xUARTQueue, &Total, pdMS_TO_TICKS(10));
	

}
	}
void Task3(void *pvParameters){
	typedef struct Message {
		char Txt1[4];
		char Txt2[4];
	} AMessage;
	AMessage msg;
	while(1){
		LCD4bits_Cmd(0x01);		  //Clear the display
	        LCD4bits_Cmd(0x80);               //Force the cursor to beginning of 1st line
		
                LCD_WriteString( " SP: " );          // print setpoint value to lcd 
		LCD4bits_Data(msg.Txt2);	
		LCD_WriteString( " MP:" ); //  // print measured value to lcd 
		LCD_WriteString( msg.Txt1);
		LCD_WriteString( "   " );
		delayMs(500);														//Delay 500 ms to let the LCD diplays the da
	
	}
}

int main(void)
{   
	xUARTQueue=xQueueCreate(1,1);
	xLCDQueue=xQueueCreate(1,8);
	ADC_init();//Initialization of potentiometer
	LCD4bits_Init();//Initialization of LCD
	xTaskCreate((TaskFunction_t)Task1,"Main Controller", configMINIMAL_STACK_SIZE,NULL,1,NULL);
	xTaskCreate((TaskFunction_t)Task2,"UART Controller", configMINIMAL_STACK_SIZE,NULL,1,NULL);
	xTaskCreate((TaskFunction_t)Task3,"LCD Controller", configMINIMAL_STACK_SIZE,NULL,1,NULL);
	vTaskStartScheduler();
}
void vApplicationIdleHook( void ){
	__asm("WFI");
}