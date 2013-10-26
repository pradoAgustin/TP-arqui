#include "../include/stdio.h"
#include "../include/stdlib.h"
#include "../include/kc.h"
#include "../include/stdarg.h"
extern char read();
extern char registers();
int cursoraux;
int r_shift;
int l_shift;
int l_control;
int r_control;
int Bloq_Mayus;
/***************************************************************
*  Funciones de entrada y salida de caracteres
****************************************************************/

/***************************************************************
* tratamos de leer e imprimir lo que leemos de teclado
wiki.osdev.org/Inline_Assembly
****************************************************************/

char getchar(){


	while(1){
		int EAX,EBX,ECX,EDX,ESI,EDI, ESP, EBP;
		char d,a;
		char c = read();
		if(c-80>0 )
			return 0;
		
		if(c==(char)0x36 && r_shift==0 ){//00110110
			r_shift=1; //right shift down code
			return 0;
			}
		if(c==(char)0xB6 && r_shift==1  ) { //10110110
			r_shift=0; // right shift up code
			return 0;
			}
		if(c==(char)0x2A && l_shift==0 ){//00101010
			l_shift=1; //left shift down code
			return 0;
			}
		if(c==(char)0xAA && l_shift==1 ) {//10101010 
			l_shift=0; // left shift up code
			return 0;
			}
		if(c==(char)0x1D && l_control==0 ){//00011101
			l_control=1;//left control down code
			return 0;
			}
		if(c==(char)0x9D && l_control==1 ) { //10011101
			l_control=0; // left control up code
			return 0;
			}
		if(c==(char)0xE0 && r_control==0 ){//11100000
			r_control=1; //right control down code
			return 0;
			}
		if(c==(char)0xE0 && r_control==1 ) {//11100000 
			r_control=0; // right control up code
			return 0;
			}
		if(c==(char)0x3A ){Bloq_Mayus=1;return 0;}//111010
		if(c==(char)0xBA ){Bloq_Mayus=0;return 0;}//10111010
		if(!(r_shift==1  || l_shift==1  ||Bloq_Mayus) && (r_control == 1 || l_control==1) && c==(char)0x13){
			//UBICA CURSOR DONDE DEBE REGISTERS BLA
			cursoraux=cursor;
			cursor=0;
			asm("movl $1, %%eax"
				:"=a" (EAX));
			asm("movl %%ebx, %%ebx"
				:"=b" (EBX));
			asm("movl %%ecx, %%ecx"
				:"=c" (ECX));
			asm("movl %%edx, %%edx"
				:"=d" (EDX));
				
			asm("movl %%esp, %%eax"
				:"=a" (ESP));
			asm("movl %%ebp, %%eax"
				:"=a" (EBP));
			asm("movl %%esi, %%esi"
				:"=S" (ESI));
			asm("movl %%edi, %%edi"
				:"=D" (EDI));
			printf("eax  \t 0x%x \t%d  \t\t\t\t\tcs\t   0x%d",EAX,EAX,registers());
			cursor=160;
			printf("ebx  \t 0x%x %d \t\t\t\tss  \t 0x%d",EBX,EBX, registers());
			cursor=320;
			printf("ecx  \t 0x%x \t%d  \t\t\t\t\tds  \t 0x%d",ECX, ECX, registers());
			cursor=480;
			printf("edx  \t 0x%x\t%d \t\t\t\t\tes  \t 0x%d",EDX, EDX, registers());
			cursor=640;
			printf("esi  \t 0x%x %d \t\t\t\tfs  \t 0x%d",ESI, ESI, registers());
			cursor=800;
			printf("edi  \t 0x%x %d \t\t\t\tgs  \t 0x%d",EDI, EDI, registers());
			cursor=960;
			printf("ebp  \t 0x%x\t%d", registers(),registers());
			cursor=1120;
			printf("esp  \t 0x%x\t%d", registers(),registers());
			cursor=1280;
			printf("eflags\t0x%x\t%d", registers(),registers());
			cursor=cursoraux;
			printf("\n");
			return 0;
		}
		
		if((r_shift==1 || l_shift==1) || Bloq_Mayus){
			d=scanCodeToASCIIshifted(c);
			printf("%c",d); //down code tabla especial
			return 0;

		}
		
	
		
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

		if (c!=0){
		
			stdout[i] = c;
			i++;
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
	int ival;
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
