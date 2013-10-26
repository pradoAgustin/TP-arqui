#include "../include/kc.h"


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
	//char* character =(char *) measure_ram();
	while(i < (80*25*2))
	{//printf2(character, 25);

		vidmem[i]= ' ';
		i++;
		vidmem[i]=WHITE_TXT;
		i++;
	}
	

}
/***************************************************************
*k_clear_screen2
*
* Borra la pantalla en modo texto color.//la parte de abajo solo
****************************************************************/

void k_clear_screen2() 
{
	char *vidmem = (char *) 0xb8000;
	unsigned int i=160*10;
	while(i < (80*25*2))
	{	vidmem[i]= ' ';
		i++;
		vidmem[i]=WHITE_TXT;
		i++;
	}
	

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



