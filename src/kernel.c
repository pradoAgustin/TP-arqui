#include "../include/kasm.h"
#include "../include/defs.h"
#include "../include/buffer.h"
DESCR_INT idt[0xA];			/* IDT de 10 entradas*/
IDTR idtr;				/* IDTR */
int tickpos=640;
#define WRITE 0
#define READ 1
extern _iniciar_contador();
extern _initialize_cursor();
// typedef struct{
// 	int eax;
// 	int ebx;
// 	int ecx;
// 	int edx;
// 	int edi;
// 	int esi;
// 	int esp;
// 	int ebp;
// } registers;

// registers w;
int w[9];


void initializeSpecialKeys(){
	k.r_control=0;
	k.r_shift=0;
	k.l_shift=0;
	k.l_control=0;
	
}


// void int_80(unsigned int sysCall, unsigned int arg1, int arg2, int arg3, int arg4, int arg5){
//    if(sysCall==WRITE)
//             __write((int)arg1, (void *)arg2, (int)arg3);
           
//     else if(sysCall==READ) 
//             __read((int)arg1, (void *)arg2,(int)arg3);
    
// }


void int_08() {

    char *video = (char *) 0xb8000;
    //video[tickpos+=2]='*';
}

void int_09(char c){
		int flag;
		int bit=1;

		// flag = read_flags();
		// flags[0]=flag<<2 & bit;
		// flags[1]=flag<<6 & bit;
		// flags[2]=flag<<9 & bit;
		// flags[3]=flag<<21 & bit;

		s.cs = read_segment_cs();
		s.ss = read_segment_ss();
		s.ds = read_segment_ds();
		s.es = read_segment_es();
		s.fs = read_segment_fs();
		s.gs = read_segment_gs();

		// w.eax = read_register_eax();
		// w.ebx = read_register_ebx();
		// w.ecx = read_register_ecx();
		// w.edx = read_register_edx();
		// w.esp = read_register_esp();
		// w.ebp = read_register_ebp();
		// w.esi = read_register_esi();
		// w.edi = read_register_edi();
		w[0]= read_register_eax();
		w[1] = read_register_ebx();
		w[2] = read_register_ecx();
		w[3] = read_register_edx();
		w[4] = read_register_esp();
		w[5] = read_register_ebp();
		w[6] = read_register_esi();
		w[7] = read_register_edi();
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
		else if(c==(char)0xE0 && k.r_control==1 ) {//11100000 
			k.r_control=0; // right control up code
			return;
			}
		else if(c==(char)0xE0 && k.r_control==0 ){//11100000
			k.r_control=1; //right control down code
			return;
			}
		else if(c==(char)0x3A && k.Bloq_Mayus==0){//111010
			k.Bloq_Mayus=1;
			return;
			}
		else if(c==(char)0x3A && k.Bloq_Mayus ==1){//0xba//10111010
			k.Bloq_Mayus=0;
			return;
			}
		else if(c & 0x80)
				return;
		else if(!(k.r_shift==1  || k.l_shift==1  ||k.Bloq_Mayus) && (k.l_control==1) && c==(char)0x13){
			
			k_clear_upper_screen();
			print_registers();
			return;
		}
		else if((k.r_shift==1 || k.l_shift==1) || k.Bloq_Mayus){
			d=scanCodeToASCIIshifted(c);

			if((((d-63) > 0 && (d-33)<0 )&& d!=10 && d!=32 && d!=8&& d!=15) || d == 42 || d == 1)
			 	return;
			 // 	if((d-64<0 && d!=10 && d!=32 && d!=8&& d!=15) || d == 42)
			 // 	{
			 // 		return;  
				// }
			storeInBuffer(d);	
			
		}
		// else if((((d=scanCodeToASCII(c))-80 < 0)&& d!=10 && d!=32 && d!=8 && d!=15)|| d == 42 || d == 1)//10 ascii del enter, 32 del espacio,08 del backspace,15 tab
		// 	{
		// 		return;
		// 	}
		else if(((d=scanCodeToASCII(c))-63 > 0 && ((d-33)<0 )&& d!=10 && d!=32 && d!=8 && d!=15)|| d == 42 || d == 1)//10 ascii del enter, 32 del espacio,08 del backspace,15 tab
			return;
		
		else
		{
		d=scanCodeToASCII(c);
		storeInBuffer(d);
		}

}
/**********************************************
kmain() 
Punto de entrada de cóo C.
*************************************************/

kmain() 
{int c;
cursor = 0;
initializeSpecialKeys();
_initialize_cursor();
initializeBuffer();

/* Borra la pantalla. */ 

	k_clear_screen();
	

/* CARGA DE IDT CON LA RUTINA DE ATENCION DE IRQ0    */

        setup_IDT_entry (&idt[0x08], 0x08, (dword)&_int_08_hand, ACS_INT, 0);
		setup_IDT_entry (&idt[0x09], 0x08, (dword)&_int_09_hand, ACS_INT, 0);
	//	setup_IDT_entry (&idt[0x80], 0x08, (dword)&_int_80_hand, ACS_INT, 0);

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
	
	showSplashScreen();
	
	initialize_screen();
    
        while(1)
        {
		shell();
        }
	
}



