#include "../include/defs.h"
#include "../include/kc.h"
int cursoraux;
int registers[20];
int flags[5];

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
			printf("eax  \t%x \t\t%d \t\t\t\t\t\tcs  \t%x %d",registers[0],registers[0],registers[8],registers[8]);
			cursor=160;
			printf("ebx  \t%x \t%d \t\t\t\t\tss  \t%x %d",registers[1],registers[1], registers[9],registers[9]);
			cursor=320;
			printf("ecx  \t%x \t\t%d \t\t\t\t\t\tds  \t%x %d",registers[2], registers[2], registers[10],registers[10]);
			cursor=480;
			printf("edx  \t%x    \t%d\t\t\t\t\t\tes  \t%x %d",registers[3], registers[3], registers[11],registers[11]);
			cursor=640;
			printf("esi  \t%x \t%d \t\t\t\t\tfs  \t%x %d",registers[6], registers[6],registers[12],registers[12]);
			cursor=800;
			printf("edi  \t%x \t%d \t\t\t\t\tgs  \t%x %d",registers[7], registers[7], registers[13],registers[13]);
			cursor=960;
			printf("ebp  \t%x \t%d", registers[5],registers[5]);
			cursor=1120;
			printf("esp  \t%x \t%d", registers[4],registers[4]);
			cursor=1280;
			printf("eflags \t%x \t[PF ZF IF ID]", flags[0]);// PF=PARITY FLAG, ZF=ZERO FLAG, IF=INTERRUMPT ENABLE FLAG ID=ID FLAG
			cursor=cursoraux;
			printf("\n");
}