
#include <stdint.h>
#include <FreeRTOS.h>
#include "tm4c123gh6pm.h"
#include "system_TM4C123.h"
#include "semphr.h"
#include "TM4C123GH6PM.h"
#include "TM4C123.h"    // Device header
#define LCD GPIOB    		//LCD port with Tiva C 
#define RS 0x01				 	//RS -> PB0 (0x01)
#define RW 0x02         //RW -> PB1 (0x02)
#define EN 0x04  		 	 	//EN -> PB2 (0x04)
void LCD4bits_Init(void);													 //Initialization of LCD Dispaly
void LCD_Write4bits(unsigned char, unsigned char); //Write data as (4 bits) on LCD
void LCD_WriteString(char*);											 //Write a string on LCD 
void LCD4bits_Cmd(unsigned char);									 //Write command 
void LCD4bits_Data(unsigned char);								 //Write a character
void delayUs(int);   														   //Delay in Micro Seconds
void delayMs(int); 