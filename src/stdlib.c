#include "../include/stdlib.h"




/**********************************************
* string functions
*************************************************/

/**********************************************
* atoi (capitulo 2 K&R pag 47)
*************************************************/
int atoi(char s[]){
int i, n;
n=0;
	for(i=0; s[i]>='0'&& s[i]<'9';i++){
		n=10* n+(s[i]-'0');
	return n;
	}
}

/**********************************************
* itoa, convierte numero en cualquier base en string 
*************************************************/
void itoa ( int value, char * str, int base ){

	int i, sign;
	
	if ((sign = value) < 0) 
		value = -value;

	i = 0;
	do 
	{
		str[i++] = value % base + '0'; 
	} while ((value /= base) > 0);
	
	if (sign < 0)
		str[i++] = '-';
	str[i] = '\0';
	reverse(str, i);
return;
}

/**********************************************
* memory functions
*************************************************/
void *calloc(size_t nitems, size_t size){} 
void free(void *ptr){} 
void *malloc(size_t size){} 
void *realloc(void *ptr, size_t size){} 
