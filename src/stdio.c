#include "../include/stdio.h"
#include "../include/defs.h"
#include "../include/kc.h"
extern char read();


/***************************************************************
*  Funciones de entrada y salida de caracteres
****************************************************************/

/***************************************************************
*  printf2 (en principio no sirve, hay que reimplementarlo como quiere K&R)
****************************************************************/

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
		printf2(&d,1);
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
int putc(int c, FILE* stream){

;

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
int printf(const char * format, ...){}

void va_start(char * ap,char * format);
void * va_arg(char *ap,void * palabra);
typedef char * va_list;
/*
//minprintf: printf minima con lista variable de argumentos 
void minprintf(char * fmt){
	va_list ap;//apunta a cada arg sin nombre en orden
	char *p, *sval;
	int ival;
	double dval;
	va_start(ap, fmt);//hace que ap apunte al 1er arg sin nombre
	for(p=fmt; *p; p++){
		if(*p!='%'){
			printf2(*p,1);//putchar(*p);//necesitaria hacer putchar LPM
			continue;	
		}
			switch(*++p){
				case 'd':
					ival= va_arg(ap,int);
					printf("%d",ival);
					break;
				case 'f':
					dval= va_arg(ap,double);
					printf("%f",dval);
					break;
				case 's':
					for(sval=va_arg(ap,char*);*sval;sval++)
						printf2(*sval,1);//putchar(*sval);
					break;	
				default:
					putchar(*p);
					break;
			}
		}
		va_end(ap); //limpia cuando todo esta hecho

}


*/

//va_start(ap, fmt);
