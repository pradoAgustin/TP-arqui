#include "../include/stdio.h"



/***************************************************************
*  Funciones de entrada y salida de caracteres
****************************************************************/

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
int scanf(const char * format,...){
}



/***************************************************************
* Salida con formato
****************************************************************/

/***************************************************************
*  printf (si)(basada en minprintf de K&R cap 7, pag 172, 173)
****************************************************************/
int printf(const char * format, ...){}


/*
minprintf: printf minima con lista variable de argumentos 
void minprintf(char * fmt){
va_list ap;//apunta a cada arg sin nombre en orden
char *p, *sval;
int ival;
double dval;
va_start(ap, fmt);//hace que ap apunte al 1er arg sin nomre
for(p=fmt; *p; p++){
	if(*p!='%'){
		putchar(*p);//necesitaria hacer putchar LPM
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
				putchar(*sval);
			break;	
		default:
			putchar(*p);
			break;
		}
	}
	va_end(ap); //limpia cuando todo esta hecho
}


*/






