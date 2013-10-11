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
* memory functions
*************************************************/
void *calloc(size_t nitems, size_t size){} 
void free(void *ptr){} 
void *malloc(size_t size){} 
void *realloc(void *ptr, size_t size){} 
