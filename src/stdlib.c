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

void itoa ( int value, char * str, int base ){
int i, sign;
if(base==16){
				if ((sign = value) < 0) 
					value = -value;

				i = 0;
				do 
				{
					if((value % base)>9){
					switch(value%base){
					case 10: {str[i++]='A';}
							break;	
					case 11: {str[i++]='B';}
							break;
					case 12: {str[i++]='C';}
							break;
					case 13: {str[i++]='D';}
							break;
					case 14: {str[i++]='E';}
							break;
					case 15: {str[i++]='F';}
							break;
					default:{}
							break;
						}
					}else 
					str[i++] = value % base + '0'; 
				} while ((value /= base) > 0);

				if (sign < 0)
					str[i++] = '-';
				str[i]='x';
				i++;
				str[i]='0';
				i++;
				str[i] = '\0';
				reverse(str, i);
			return;
			}	
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