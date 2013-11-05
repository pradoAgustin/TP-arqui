#include "../include/ctype.h"


int isalnum(int character);
int isalpha(int character);
int iscntrl(int character);
int isdigit(char character){
	return character >= '0' && character <= '9';
}
int
ishexa(char character){
	return (character>='a' && character<= 'f');
}




int isgraph(int character);
int islower(int character);
int isprint(int character);
int ispunct(int character);
int isspace(int character);
int isupper(int character);
int isxdigit(int character);
