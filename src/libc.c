#include "../include/kc.h"
#define ESC 1
#define INV 1
extern char read();
#include "../include/defs.h"

/***************************************************************
*  printf
****************************************************************/

void printf(char* chain, int quantity)
{
	int i=0,j=0 ;
	char* videomem = (char *)(POSITION+ cursor) ;

	while(j < quantity){
		if(chain[j]=='\b')
			{	
			backspace();
			return;
			}
		if(chain[j]=='\n')
			{	
			enter();
			return;
			}
		if(chain[j]=='\t')
			{	
			tab();
			return;
			}

		if (chain[j]!=0){
		
			videomem[i] = chain[j];
			i++;
			j++;
			videomem[i] = WHITE_TXT;
			i++;
			}
			else
				return ;
		
		}
		cursor+=i;

}

/***************************************************************
*k_clear_screen
*
* Borra la pantalla en modo texto color.
****************************************************************/

void k_clear_screen() 
{
	int h=0;
	char *vidmem = (char *) 0xb8000;
	unsigned int i=0;
	while(i < (80*25*2))
	{
		vidmem[i]= ' ';
		i++;
		vidmem[i]=WHITE_TXT;
		i++;
	}
	//char caracter = measure_ram();
//printf(measure_ram());

}

/***************************************************************
* enter
****************************************************************/

void enter()
{
	cursor+=160 - cursor%160;
}
 
/***************************************************************
*tab
****************************************************************/
void tab()
{
	cursor += TAB;
} 

/***************************************************************
* tratamos de leer e imprimir lo que leemos de teclado
****************************************************************/

char getchar(){
	

char scanCodeToASCII[0xff] =
{    /*  0    1    2    3    4    5    6    7    8    9    A    B    C    D    E     F    */
/*0*/   INV, ESC, '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '\'', INV, '\b', '\t',
 
/*1*/   'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', INV, '+', '\n', INV, 'a', 's',
 
/*2*/   'd', 'f', 'g', 'h', 'j', 'k', 'l', INV, '{', '}', INV, '<', 'z', 'x', 'c', 'v',
 
/*3*/   'b', 'n', 'm', ',', '.', '/', INV, '*', INV, ' ', INV, 0xB3, INV, INV, INV, INV,
 
/*4*/   INV, INV, INV, INV, INV, INV, INV, '7', '8', '9', '-', '4', '5', '6', '+', '1',
 
/*5*/   '2', '3', '0', '.', INV, INV, INV, INV, INV, INV, INV, INV, INV, INV, INV, INV
 
};

char scanCodeToASCII2[0xff] =
{    /*  0    1    2    3    4    5    6    7    8    9    A    B    C    D    E     F    */
/*0*/   INV, ESC, '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '\'', INV, '\b', '\t',
 
/*1*/   'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P', INV, '+', '\n', INV, 'A', 'S',
 
/*2*/   'D', 'F', 'G', 'H', 'J', 'K', 'L', INV, '{', '}', SHIFT, '<', 'Z', 'X', 'C', 'V',
 
/*3*/   'B', 'N', 'M', ',', '.', '/', INV, '*', INV, ' ', INV, 0xB3, INV, INV, INV, INV,
 
/*4*/   INV, INV, INV, INV, INV, INV, INV, '7', '8', '9', '-', '4', '5', '6', '+', '1',
 
/*5*/   '2', '3', '0', '.', INV, INV, INV, INV, INV, INV, INV, INV, INV, INV, INV, INV
 
};
	
	while(1){
		char d;
		char c = read();
		if(c-80>0)
			return 0;
		d=scanCodeToASCII[c];
		printf(&d,1);
	}
}


void backspace()
{
	cursor -=2;
	char* videomem = (char *)(POSITION + cursor) ;
	videomem[0] = ' '; 


}

/***************************************************************
*setup_IDT_entry
* Inicializa un descriptor de la IDT
*
*Recibe: Puntero a elemento de la IDT
*	 Selector a cargar en el descriptor de interrupcion
*	 Puntero a rutina de atencion de interrupcion	
*	 Derechos de acceso del segmento
*	 Cero
****************************************************************/

void setup_IDT_entry (DESCR_INT *item, byte selector, dword offset, byte access,
			 byte cero) {
  item->selector = selector;
  item->offset_l = offset & 0xFFFF;
  item->offset_h = offset >> 16;
  item->access = access;
  item->cero = cero;
}


/***************************************************************
ver cantidad de memoria del sistema
****************************************************************/
unsigned long measure_ram(void)
{
	int * pos = (int*)0x100000;
	do
	{
		pos += 0x1000; //0001 0000 0000 0000 son 4k
	} while (is_available(pos));
	
	return (unsigned long)pos;
}

int is_available(int * pos)
{
	*pos = CONTROL_INT;
	if (*pos == CONTROL_INT)
		return TRUE;
	return FALSE;
}
