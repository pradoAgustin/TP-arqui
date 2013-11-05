#include "../include/kasm.h"
#include "../include/defs.h"
#include "../include/buffer.h"

DESCR_INT idt[0xA];			/* IDT de 10 entradas*/
IDTR idtr;				/* IDTR */
int cursoraux;
int tickpos=640;
int prompt2;
int registers[20];
int flags[5];
int i;


void int_08() {

    char *video = (char *) 0xb8000;
    //video[tickpos+=2]='*';
}

void int_09(){
		flags[0]=read_flags();
		registers[0]= read_register_eax();
		registers[1]= read_register_ebx();
		registers[2]= read_register_ecx();
		registers[3]= read_register_edx();
		registers[4]= read_register_esp();
		registers[5]= read_register_ebp();
		registers[6]= read_register_esi();
		registers[7]= read_register_edi();
			
	// EDI, ESI , EBP, EBX. EDX, ECX, EAX, 
			//acceder a la rutina de interrupcion a su stack 
			// asm("movl %%eax, %%eax"
			// 	:"=a" (registers[0]));//EAX
			// 	//ctrl R mi proceso esta con el calculo matematico, datos relativos a mi handler de write esta mal
			// asm("movl %%ebx, %%ebx"
			// 	:"=b" (registers[1]));//EBX
			// asm("movl %%ecx, %%ecx"
			// 	:"=c" (registers[2]));//ECX
			// asm("movl %%edx, %%edx"
			// 	:"=d" (registers[3]));//EDX	
			// asm("movl %%esp, %%eax"
			// 	:"=a" (registers[4]));//ESP
			// asm("movl %%ebp, %%eax"
			// 	:"=a" (registers[5]));//EBP
			// asm("movl %%esi, %%esi"
			// 	:"=S" (registers[6]));//ESI
			// asm("movl %%edi, %%edi"
			// 	:"=D" (registers[7]));//EDI
			// asm("xorl %%eax, %%eax\n"
			// 	"movw %%cs, %%eax" //http://www.eecg.toronto.edu/~amza/www.mindsec.com/files/x86regs.html
			// 	:"=a" (registers[8]));//CS
			// asm("xorl %%eax, %%eax\n"
			// 	"movw %%ss,%%ax "
			// 	:"=a" (registers[9]));//SS
			// asm("xorl %%eax, %%eax\n"
			// 	"movw %%ds,%%ax "
			// 	:"=a" (registers[10]));//DS
			// asm("xorl %%eax, %%eax\n"
			// 	"movw %%es,%%ax "
			// 	:"=a" (registers[11]));//ES
			// asm("xorl %%eax, %%eax\n"
			// 	"movw %%fs,%%ax "
			// 	:"=a" (registers[12]));//FS
			// asm("xorl %%eax, %%eax\n"
			// 	"movw %%gs,%%ax "
			// 	:"=a" (registers[13]));//GS
			//codigo divino para ctrl R y mayusculas
	
  //guardo en assembler los registros
//__save_registers();
    __write(1,1,1);
shell();
	//__read(1,1,1);
	//shell();
}

/**********************************************
kmain() 
Punto de entrada de cóo C.
*************************************************/

kmain() 
{cursor=0;
prompt2=1;
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
//shell();

        while(1)
        {
		//shell();
        }
	
}

