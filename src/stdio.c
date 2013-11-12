#include "../include/stdio.h"
#include "../include/stdlib.h"
#include "../include/kc.h"
#include "../include/stdarg.h"
#include "../include/buffer.h"
int printf( char * fmt, ...);
/***************************************************************
*  Funciones de entrada y salida de caracteres
****************************************************************/

/***************************************************************
* tratamos de leer e imprimir lo que leemos de teclado
wiki.osdev.org/Inline_Assembly
****************************************************************/

int getchar(){
	return __read(1,1,1);
}

/***************************************************************
*  getc (si)
****************************************************************/
int getc(FILE * stream){
	while( __read(1,1,1) == 0)
		return 0 ;
	return getc((FILE *)1);
}

/***************************************************************
*  putc (si)
****************************************************************/
int putc(char c, FILE * stdout){
	
	int i=0 ;
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
	update_cursor();
	if(stdout==(FILE *)1 && c!=0){
		__write(1,c,1);
	}	
	
cursor+=i;
if(cursor>(160*25)){
	k_scroll();
	cursor=77*2*25-8;
}
}

/***************************************************************
*  puts (si)
****************************************************************/
int puts( FILE * stream){

	while(*stream){
		putc(*stream, (char *)1);//POSITION+cursor);//(char*)2);
		stream++;	
	}
}

/***************************************************************
*  Entrada con formato
****************************************************************/

/***************************************************************
* scanf (si)(tambien resolver con la idea de minprintf ya que tmb usa func de argumentos variables)
****************************************************************/

int scanf(const char * fmt, ...){
	va_list ap; //apunta a cada arg sin nombre en orden
	char *p, *sval, *cval;
	int *ival;
	FILE  fp;
	int read=0,i=0, c,k, j = 0;
	va_start(ap, fmt); //hace que ap apunte al 1er arg sin nombre
	char s[BUFFER_SIZE];
	while((c = getchar()) != '\n' && i < BUFFER_SIZE)
	{
		if(c!=0){
			if(c == '\b' && i >= 1){
				i--;
				putc(c ,(FILE*)1);
			}
			if(c != '\b' && c!='\n'){
				s[i] = c;
				i++;
				putc(c ,(FILE *)1);	
			}
		}
	}
	s[i] = '\0';
	i = 0;
		for (p = (char*)fmt; *p; p++) 
		{
			char aux [BUFFER_SIZE] = {0};

			if(*p != '%')
			{
				c = s[j++];
				if(c =='\0' || *p != c)
					return read;
				continue;
			}
			switch (*++p)
			{
				case 'd':
							i=0;
							ival = va_arg(ap,int *);
							while(s[j] != '\0' && isdigit(s[j]))
							{
								aux[i++] = s[j++];
							}
							aux[i] = '\0';
							if(aux[0] == '\0')
								return read;
							*ival=atoi(aux);
							read++;
							break;
				case 's':
							i = 0;
							sval = va_arg(ap,char *);
							while(s[j] != '\0' && s[j] != ' ')
							{
								aux[i++] = s[j++];
							}
							aux[i] = '\0';
							if(aux[0] == '\0')
								return read;
							
							k = 0;
							while(aux[k] != '\0')
							{
								sval[k] = aux[k];
								k++;
							}
							sval[k] = '\0';
							read++;
							break;
				case 'c':
							cval = va_arg(ap,char*);
							c = s[j++];
							if(c == '\0' )
								return read;
							*cval = c;
							read++;
							break;
				case 'x':
							i=0;
							ival = va_arg(ap,int *);
							while(s[j] != '\0' && (isdigit(s[j]) || ishexa(s[j])))
							{
								aux[i] = s[j];
								i++;
								j++;
							}
							aux[i] = '\0';
							if(aux[0] == '\0')
								return read;
							//*ival=ato(aux, i, 16);
							read++;
							break;
			
				default:
							c = s[j++];
							if(!(c != EOF && c != '\n' && *p == c))
								return read;
							break;
			}
		}
	va_end(ap); // clean up when done
	return read;
}


/***************************************************************
* Salida con formato
****************************************************************/
/***************************************************************
*  printf (si)(basada en minprintf de K&R cap 7, pag 172, 173)
****************************************************************/

int printf( char * fmt, ...){
	va_list ap;//apunta a cada arg sin nombre en orden
	char *p, *sval;
	int ival;
	char s[MAX_LENGTH];
	va_start(ap, fmt);//hace que ap apunte al 1er arg sin nombre
	for(p=fmt; *p; p++){
		if(*p!='%'){
			putc(*p,(char*)1);//(POSITION+cursor));//NOOOOOOOOOOO
			continue;	
		}
		switch(*++p){
			case 'd':
				ival= va_arg(ap,int);
				itoa(ival,s,10);
				puts(s);
				break;
			case 'x':
				ival= va_arg(ap,int);
				itoa(ival,s,16);
				puts(s);
				break;
			case 'c':
				ival= va_arg(ap,int);	
				if(cursor == (80*2*25)){cursor=80*24*2;k_scroll();prompt2=0;}				
					putc(ival,(char*)1);//(POSITION+cursor));//NOOOOOOOOOOOOOO
					break;
			case 's':
				for(sval=va_arg(ap,char*);*sval;sval++)
					putc(*sval, (char*)1);//(POSITION+cursor) );//NOOOOOOOOOOOOOOOOOOOOOOOOO
				break;
			default:
				putc(*p,(char*)1);//(POSITION+cursor));//NOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOO
				break;
				}
			}
		va_end(ap); //limpia cuando todo esta hecho
		return 0;
	}
