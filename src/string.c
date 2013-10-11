#include "../include/string.h"
/**********************************************
* strlen(capitulo 2 K&R pag 43)(va en string)
*************************************************/

int strlen(char s[]){
int i;
i=0;
	while (s[i]!='\0'){
	++i;	
	}
return i;
}
