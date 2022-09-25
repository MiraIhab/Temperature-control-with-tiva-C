#include <stdio.h>  
#include <math.h>  
#include <stdlib.h>  
#include "ITOA.h"
char* myitoa(int num, char* buffer, int base)   
{  
int current = 0;  
if (num == 0) {  
buffer[current++] = '0';  
buffer[current] = '\0';  
return buffer;  
}  
int num_digits = 0;  
 
num_digits += (int)floor(log(num) / log(base)) + 1;  
while (current < num_digits)   
{  
int base_val = (int) pow(base, num_digits-1-current);  
int num_val = num / base_val;  
 char value = num_val + '0';  
buffer[current] = value;  
current ++;  
num -= base_val * num_val;  
}  
buffer[current] = '\0';  
return buffer;  
}  