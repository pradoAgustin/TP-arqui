#include "../include/defs.h"
#include "../include/kc.h"
int w [5];
/***************************************************************
*k_scroll
* scrolleaaa.//la parte de abajo solo
****************************************************************/

void k_scroll() 
{
	char *vidmem = (char *) 0xb8000;
	unsigned int i=160*10;
	while(i < (80*25*2))
	{	vidmem[i]= vidmem[i+160];
		i++;
		vidmem[i]=WHITE_TXT;
		i++;		
	}
}



void update_cursor() { 
	unsigned short position = cursor; 
	if (position != 0) { 
		outportb(0x3D4, 0x0F); 
		outportb(0x3D5, (unsigned char)(position/2)); 
		outportb(0x3D4, 0x0E); 
		outportb(0x3D5, (unsigned char )(((position/2)>>8)));
	}
}

print_registers(){
			cursoraux=cursor;
			cursor=0;
			printf("eax  \t%x \t\t%d",w[0],w[0]);
			cursor=0;
			printf("\t\t\t\t\t\t\t\t\t\tcs  \t%x %d",s.cs,s.cs);
			cursor=160;
			printf("ebx  \t%x \t%d",w[1],w[1]);
			cursor=160;
			printf("\t\t\t\t\t\t\t\t\t\tss  \t%x %d",s.ss,s.ss);
			cursor=320;
			printf("ecx  \t%x \t%d",w[2], w[2]);
			cursor=320;
			printf("\t\t\t\t\t\t\t\t\t\tds  \t%x %d", s.ds,s.ds);
			cursor=480;
			printf("edx  \t%x \t%d",w[3], w[3]);
			cursor=480;
			printf("\t\t\t\t\t\t\t\t\t\tes  \t%x %d", s.es,s.es);
			cursor=640;
			printf("esi  \t%x \t%d",w[4], w[4]);
			cursor=640;
			printf("\t\t\t\t\t\t\t\t\t\tfs  \t%x %d",s.fs,s.fs);
			cursor=800;
			printf("edi  \t%x \t%d",w[5], w[5]);
			cursor=800;
			printf("\t\t\t\t\t\t\t\t\t\tgs  \t%x %d",s.gs,s.gs);
			cursor=960;
			printf("ebp  \t%x \t%d", w[6],w[6]);
			cursor=1120;
			printf("esp  \t%x \t%d", w[7],w[7]);
			cursor=1280;
			//printf("eflags \t%x \t[PF ZF IF ID]", flags);// PF=PARITY FLAG, ZF=ZERO FLAG, IF=INTERRUMPT ENABLE FLAG ID=ID FLAG
			cursor=cursoraux;
			update_cursor();
}


void initialize_screen(){
	k_clear_screen();
cursor=160*9;
printf("________________________________________________________________________________");
cursor=160*10;
prompt();
update_cursor();
}