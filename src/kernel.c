#include "../include/kasm.h"
#include "../include/defs.h"
#include "../include/buffer.h"
int r_shift;
int l_shift;
int l_control;
int r_control;
DESCR_INT idt[0xA];			/* IDT de 10 entradas*/
IDTR idtr;				/* IDTR */
int cursoraux;
int Bloq_Mayus;
int tickpos=640;
int prompt2;


void int_08() {

    char *video = (char *) 0xb8000;
    //video[tickpos+=2]='*';

}

void int_09(){
char *video = (char *) 0xb8000;
	
  
    __write(1,1,1);
	
	__read(1,1,1);
}

/**********************************************
kmain() 
Punto de entrada de cóo C.
*************************************************/

kmain() 
{cursor=0;
//char * STDOUT1 = POSITION + cursor;  // INICIALIZO MI PRIMER FILE DESCRIPTOR
cursor=15*160;
//char STDOUT2 =POSITION +cursor;  // INICIALIZO MI SEGUNDO FILE DESCRIPTOR
cursor=160*10;
r_shift=0,l_shift=0, l_control=0, r_control=0,prompt2=1;
int i,num,j,w,z,q;


/* Borra la pantalla. */ 

	k_clear_screen();
	

/* CARGA DE IDT CON LA RUTINA DE ATENCION DE IRQ0    */

        setup_IDT_entry (&idt[0x08], 0x08, (dword)&_int_08_hand, ACS_INT, 0);
		setup_IDT_entry (&idt[0x09], 0x08, (dword)&_int_09_hand, ACS_INT, 0);
/* Carga de IDTR    */

	idtr.base = 0;  
	idtr.base +=(dword) &idt;
	idtr.limit = sizeof(idt)-1;
	
	_lidt (&idtr);	

	_Cli();
/* Habilito interrupcion de timer tick*/

        _mascaraPIC1(0xFC);
        _mascaraPIC2(0xFF);
        
	_Sti();





/* Llamo a getchar para probar mi codigo, hecho por mi*/	
cursor=160*9;
printf("________________________________________________________________________________");
cursor=160*10;
//	prompt();


cursor=0;
//for(z=0;z<11;z++){
	//for(q=0;q<80;q++){
		//STDOUT1[z][q]='4';
		//printf("%c",STDOUT1[z][q]);
		
//	}
	
//}
//cursor=160*10;

//PRINT SCREEN

cursor=160*9;
printf("________________________________________________________________________________");
cursor=160*10;
prompt();

//while(z<296){printf("hola");z++;}
//getPci();
        while(1)
        {
		
        }
	
}

