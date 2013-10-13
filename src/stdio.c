#include "../include/stdio.h"
#include "../include/stdlib.h"
#include "../include/kc.h"
#include "../include/stdarg.h"
extern char read();


/***************************************************************
*  Funciones de entrada y salida de caracteres
****************************************************************/

/***************************************************************
*  printf2 (bueno mientras duro)
****************************************************************/
/*
void printf2(char* chain, int quantity)
{
	int i=0,j=0 ;
	char* videomem = (char *)(POSITION+ cursor) ;

	while(j < quantity){
		if(chain[j]=='\b')
			{	
			backspace();
			return;
			}
		if(chain[j]=='\n')
			{	
			enter();
			return;
			}
		if(chain[j]=='\t')
			{	
			tab();
			return;
			}

		if (chain[j]!=0){
		
			videomem[i] = chain[j];
			i++;
			j++;
			videomem[i] = WHITE_TXT;
			i++;
			}
			else
				return ;
		
		}
		cursor+=i;

}

*/
/***************************************************************
* tratamos de leer e imprimir lo que leemos de teclado
****************************************************************/

char getchar(){

	while(1){
		
		char d;
		char c = read();
		if(c-80>0)
			return 0;
		
		d=scanCodeToASCII(c);
		printf("%c",d);
	}
}


/***************************************************************
*  getc (si)
****************************************************************/
int getc(FILE * stream){
;



}
/***************************************************************
*  putc (si)
****************************************************************/
int putc(int c, FILE * stdout){
	
	int i=0,j=0 ;
		if(c=='\b')
			{	
			backspace();
			return;
			}
		if(c=='\n')
			{	
			enter();
			return;
			}
		if(c=='\t')
			{	
			tab();
			return;
			}

		if (c!=0){
		
			stdout[i] = c;
			i++;
			j++;
			stdout[i] = WHITE_TXT;
			i++;
			}
			else
				return ;
		
	
		cursor+=i;

}

/***************************************************************
*  puts (si)
****************************************************************/
int puts( FILE * stream){

	while(*stream){
		putc(*stream, (char*)(POSITION+cursor));
		stream++;	
	}
}

/***************************************************************
*  Entrada con formato
****************************************************************/

/***************************************************************
* scanf (si)(tambien resolver con la idea de minprintf ya que tmb usa func de argumentos variables)
****************************************************************/
int scanf(const char * format, ...){
}



/***************************************************************
* Salida con formato
****************************************************************/

/***************************************************************
*  printf (si)(basada en minprintf de K&R cap 7, pag 172, 173)
****************************************************************/

int printf( char * fmt,...){
	va_list ap;//apunta a cada arg sin nombre en orden
	char *p, *sval;
	int ival,base=10;
	char s[MAX_LENGTH];
	va_start(ap, fmt);//hace que ap apunte al 1er arg sin nombre
	for(p=fmt; *p; p++){
		if(*p!='%'){
			putc(*p,(char*)(POSITION+cursor));
			continue;	
		}
			switch(*++p){
				case 'd':
					ival= va_arg(ap,int);
					itoa(ival, s, base);
					puts(s);
					break;
				case 'x':
					ival= va_arg(ap,int);
					itoa(ival, s, 16);
					puts(s);
					break;
				case 'c':
					ival= va_arg(ap,int);					
					putc(ival, (char*)(POSITION+cursor));
					break;
				case 's':
					for(sval=va_arg(ap,char*);*sval;sval++)
						putc(*sval, (char*)(POSITION+cursor) );
					break;	
				default:
					putc(*p, (char*)(POSITION+cursor));
					break;
			}
		}
		va_end(ap); //limpia cuando todo esta hecho
	return 0;
}
