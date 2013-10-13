#include "../include/string.h"
/**********************************************
* strlen(capitulo 2 K&R pag 43)
*************************************************/

int strlen(char s[]){
int i;
i=0;
	while (s[i]!='\0'){
	++i;	
	}
return i;
}

/**********************************************
* reverse da vuelta un string, auxiliar de itoa
*************************************************/

void 
reverse(char s[], int size)
{
	int i;
	for(i = 0; i < size/2; i++)
	{
		char aux = s[i];
		s[i] = s[size - i - 1];
		s[size - i - 1] = aux;
	}
	s[size] = '\0';
}



/**********************************************
* http://www.acm.uiuc.edu/webmonkeys/book/c_guide/2.14.html#variables
*************************************************/


void *memcpy(void *str1, const void *str2, size_t n);
char *strcat(char *str1, const char *str2); 
char *strchr(const char *str, int c); 
int strcmp(const char *str1, const char *str2); 
