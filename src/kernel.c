#include "../include/kasm.h"
#include "../include/defs.h"
#include "../include/buffer.h"
int segments[6];
DESCR_INT idt[0xA];			/* IDT de 10 entradas*/
IDTR idtr;				/* IDTR */
int cursoraux;
int tickpos=640;
int prompt2;
int registers[20];
int flags[5];
int i;
typedef struct{
        int r_shift;
        int l_shift;
        int r_control;
		int l_control;
		int Bloq_Mayus;
			} specialKeys;
specialKeys k;

//initializeSpecialKeys();
void initializeSpecialKeys(){
	k.r_control=0;
	k.r_shift=0;
	k.l_shift=0;
	k.l_control=0;
	
}	

void int_08() {

    char *video = (char *) 0xb8000;
    //video[tickpos+=2]='*';
}

void int_09(char c){
		int flag;
		int bit=1;
		flag=read_flags();
		flags[0]=flag<<2 & bit;
		flags[1]=flag<<6 & bit;
		flags[2]=flag<<9 & bit;

		flags[3]=flag<<21 & bit;

		segments[0] = read_segment_cs();
		segments[1] = read_segment_ss();
		segments[2] = read_segment_ds();
		segments[3] = read_segment_es();
		segments[4] = read_segment_fs();
		segments[5] = read_segment_gs();

		registers[0] = read_register_eax();
		registers[1] = read_register_ebx();
		registers[2] = read_register_ecx();
		registers[3] = read_register_edx();
		registers[4] = read_register_esp();
		registers[5] = read_register_ebp();
		registers[6] = read_register_esi();
		registers[7] = read_register_edi();
			
		char d,a;

		if(c-80>0 )
			return;

			//codigo divino para ctrl R y mayusculas
		else if(c==(char)0x36 && (k.r_shift) == 0 ){//00110110
			k.r_shift=1; //right shift down code
			return;
			}

		else if(c==(char)0xB6 && k.r_shift == 1  ) { //10110110
			k.r_shift=0; // right shift up code
			return;
			}

		else if(c==(char)0x2A && k.l_shift == 0 ){//00101010
			k.l_shift=1; //left shift down code
			return;
			}

		else if(c==(char)0xAA && k.l_shift == 1 ) {//10101010 
			k.l_shift=0; // left shift up code
			return;
			}

		else if(c==(char)0x1D && k.l_control==0 ){//00011101
			k.l_control=1;//left control down code
			return;
			}
		else if(c==(char)0x9D && k.l_control==1 ) { //10011101
			k.l_control=0; // left control up code
			return;
			}
		else if(c==(char)0xE0 && k.r_control==0 ){//11100000
			k.r_control=1; //right control down code
			return;
			}
		else if(c==(char)0xE0 && k.r_control==1 ) {//11100000 
			k.r_control=0; // right control up code
			return;
			}
		else if(c==(char)0x3A ){//111010
			k.Bloq_Mayus=1;
			return;
			}
		else if(c==(char)0xBA ){//10111010
			k.Bloq_Mayus=0;
			return;
			}

		else if(!(k.r_shift==1  || k.l_shift==1  ||k.Bloq_Mayus) && (k.r_control == 1 || k.l_control==1) && c==(char)0x13){
			//UBICA CURSOR DONDE DEBE REGISTERS BLA
			//clean upper screen
			k_clear_upper_screen();
			print_registers();
			return;
		}
		else if((k.r_shift==1 || k.l_shift==1) || k.Bloq_Mayus){//ojo aca! no printefear, guardar en buffer
			d=scanCodeToASCIIshifted(c);

			 if(d-64<0 && d!=10 && d!=32 && d!=8&& d!=15)
			 	return;	
			storeInBuffer(d);	
			
		}
		else if((d=scanCodeToASCII(c))-80<0 && d!=10 && d!=32 && d!=8 && d!=15)//10 ascii del enter, 32 del espacio,08 del backspace,15 tab
			return;
		
		else
		{
		d=scanCodeToASCII(c);
		storeInBuffer(d);
		}

  // __read(1,1,1);

}
/**********************************************
kmain() 
Punto de entrada de cóo C.
*************************************************/

kmain() 
{
cursor = 0;
prompt2 = 1;
i=0;
 //initializeBuffer();
 initializeSpecialKeys();
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
prompt();
update_cursor();

        while(1)
        {
		shell();
        }
	
}



