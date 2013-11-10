#include "../include/ctype.h"

int isdigit(char character){
	return character >= '0' && character <= '9';
}

int
ishexa(char character){
	return (character>='a' && character<= 'f');
}


