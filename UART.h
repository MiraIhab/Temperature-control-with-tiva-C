
#include <stdint.h>
#include <FreeRTOS.h>
#include "tm4c123gh6pm.h"
#include "queue.h"
#include "system_TM4C123.h"
#include "semphr.h"
#include "TM4C123GH6PM.h"
#include "TM4C123.h"    // Device header
void InitUART(void);
void UART0_Transmitter(char data);
char UART0_Receiver(void)  ;