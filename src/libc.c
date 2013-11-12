#include "../include/kc.h"

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
}

/*borra pantalla inferior*/
void k_clear_screen2(){
	int h=0;
	char *vidmem = (char *) 0xb8000;
	unsigned int i=160*10;

	while(i < (80*25*2))
	{
		vidmem[i]= ' ';
		i++;
		vidmem[i]=WHITE_TXT;
		i++;
	}
}

void k_clear_upper_screen() 
{
	int h=0;
	char *vidmem = (char *) 0xb8000;
	unsigned int i=0;

	while(i < (80*9*2))
	{

		vidmem[i]= ' ';
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

void showSplashScreen(){
char c;
cursor=0;
    printf("%s","                    _     _ _                            ");
cursor=160;
    printf("%s","__      ____ _  ___| |__ (_) |_ _   _ _ __ _ __ ___  ___ ");
cursor=320;
    printf("%s","\\ \\ /\\ / / _` |/ __| '_ \\| | __| | | | '__| '__/ _ \\/ __|");
cursor=480;
    printf("%s"," \\ V  V / (_| | (__| | | | | |_| |_| | |  | | | (_) \\__ \\");
cursor=640;
    printf("%s","  \\_/\\_/ \\__,_|\\___|_| |_|_|\\__|\\__,_|_|  |_|  \\___/|___/");
cursor=800;
    printf("%s","                                TPE Arquitectura de Computadoras");
cursor=960+160;
    printf("%s","Rivera Ignacio & Hirschowitz Kevin");
cursor=160*25;
        printf("Presione enter para continuar");



while((c=getchar())!='\n');
return;
}