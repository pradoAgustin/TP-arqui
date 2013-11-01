#include "../include/kernel.h"
#include "../include/buffer.h"
int r_shift;
int l_shift;
int l_control;
int r_control;
int cursoraux;
int Bloq_Mayus;

//preguntas

//para eflags tengo q acceder al stack(cs ip eflags) iret en la interrupcion de teclado
//shell???? separacion video y shell, diferencias
//getchar(parece demasiado simple el mio )
//int 80?
//driver de video? 
//2 buffers? 3???? ejemplo hola pepe, borra ->hola mundo
//esta bien mi acceso a registros o es un poco villero?
// pasos atapi, ingresar a todos los buses y todo los devices! ir preguntando cual es el que tiene el controlador de ata y dsp la funcionalidad del ata
// int 09 llama al writeBuffer y tmb a readBuffer o quien termina imprimiendo en pantalla
//puede ser que si tipeo rapido hay caracteres que se los saltea?
// no encuentro donde esta el cursor para q vayan los 2 a la par
//que otra opcion habria a usar cursor como variable global que no sea pasasrla por parametro??
//mis registros estan cambiando(si pongo por ejemplo un while 1 printf) pero no se si estan bien, tengo forma de comprobarlo?
//no puedo solucionar de pasarle stdout 1 y stdout2 a putchar

/* __write
*
* Recibe como parametros:
* - File Descriptor
* - Buffer del source
* - Cantidad
*
**/
size_t __write(int fd, const void* buffer, size_t count){
//while(1){
		int EAX,EBX,ECX,EDX,ESI,EDI, ESP, EBP,SS,CS,DS,ES,FS,GS;
		char d,a;
		char c = read();// lo que lee en assembbler lo pone en el buffer
		if(c-80>0 )
			return 0;
			//acceder a la rutina de interrupcion a su stack 
			asm("movl %%eax, %%eax"
				:"=a" (EAX));
				//ctrl R mi proceso esta con el calculo matematico, datos relativos a mi handler de write esta mal
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
			asm("xorl %%eax, %%eax\n"
				"movw %%cs, %%eax" //http://www.eecg.toronto.edu/~amza/www.mindsec.com/files/x86regs.html
				:"=a" (CS));
			asm("xorl %%eax, %%eax\n"
				"movw %%ss,%%ax "
				:"=a" (SS));//esta bien?
			asm("xorl %%eax, %%eax\n"
				"movw %%ds,%%ax "
				:"=a" (DS));//esta bien?
			asm("xorl %%eax, %%eax\n"
				"movw %%es,%%ax "
				:"=a" (ES));//esta bien?
			asm("xorl %%eax, %%eax\n"
				"movw %%fs,%%ax "
				:"=a" (FS));//esta bien?
			asm("xorl %%eax, %%eax\n"
				"movw %%gs,%%ax "
				:"=a" (GS));//esta bien?
			//codigo divino para ctrl R y mayusculas
		
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
			printf("eax  \t 0x%x \t%d  \t\t\t\t\tcs\t   0x%d",EAX,EAX,CS);
			cursor=160;
			
			printf("ebx  \t 0x%x %d \t\t\t\tss  \t 0x%d",EBX,EBX, SS);
			cursor=320;
			
			printf("ecx  \t 0x%x \t%d  \t\t\t\t\tds  \t 0x%d",ECX, ECX, DS);
			cursor=480;
			
			printf("edx  \t 0x%x\t%d \t\t\t\t\tes  \t 0x%d",EDX, EDX, ES);
			cursor=640;
		
			printf("esi  \t 0x%x %d \t\t\t\tfs  \t 0x%d",ESI, ESI,FS);
			cursor=800;
			
			printf("edi  \t 0x%x %d \t\t\t\tgs  \t 0x%d",EDI, EDI, GS);
			cursor=960;
			printf("ebp  \t 0x%x\t%d", EBP,EBP);
			cursor=1120;
			printf("esp  \t 0x%x\t%d", ESP,ESP);
			cursor=1280;
			printf("eflags\t0x%x\t[PF ZF IF ID]", 0);// PF=PARITY FLAG, ZF=ZERO FLAG, IF=INTERRUMPT ENABLE FLAG ID=ID FLAG
			cursor=cursoraux;
			printf("\n");
			return 0;
		}
		
		if((r_shift==1 || l_shift==1) || Bloq_Mayus){//ojo aca! no printefear, guardar en buffer
			d=scanCodeToASCIIshifted(c);
			
			storeInBuffer(d);
			
			
			return 0;
		}
				
		d=scanCodeToASCII(c);
		
		
		storeInBuffer(d);
		
//	}


}

/* __read
*
* Recibe como parametros:
* - File Descriptor
* - Buffer a donde escribir
* - Cantidad
*
**/
size_t __read(int fd, void* buffer, size_t count){
char c=getBuffer();
if(c == 0)
	return;
printf("%c",c);
}

