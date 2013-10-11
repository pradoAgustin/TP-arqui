#include "../include/kc.h"
extern char read();
#include "../include/defs.h"

/***************************************************************
*  printf (en principio no sirve, hay que reimplementarlo como quiere K&R)
****************************************************************/

void printf2(char* chain, int quantity)
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
