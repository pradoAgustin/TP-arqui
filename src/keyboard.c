extern char read();
#include "../include/defs.h"
#include "../include/keyboard.h"


/***************************************************************
*scanCodeToASCII
****************************************************************/

char scanCodeToASCII(char c){
	return scanCodeToASCII1[c];
}

/***************************************************************
* Enter
****************************************************************/

void enter(){
	if(cursor > 75*25*2){
		k_clear_screen(); 
		cursor=0;	
	}else
	cursor += 160 - cursor%160;
}
 
/***************************************************************
*Tab
****************************************************************/
void tab(){
	cursor += TAB;
} 



/***************************************************************
*backspace(hay que modificarlo para no poder borrar la linea anterior despues de un enter)
****************************************************************/
void backspace(){
	cursor -=2;
	char* videomem = (char *)(POSITION + cursor) ;
	videomem[0] = ' '; 

}

