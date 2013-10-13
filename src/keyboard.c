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
prompt();
}
 
/***************************************************************
*Tab
****************************************************************/
void tab(){
	cursor += TAB;
} 

/***************************************************************
*backspace
****************************************************************/
void backspace(){
int i,puedeBorrar=1;
	for(i=0;i<25*2*80 ;i++){
		if(cursor==(30*2+160*i))
			puedeBorrar=0;
	}
	if(puedeBorrar){			
		cursor -=2;
		char* videomem = (char *)(POSITION + cursor) ;
		videomem[0] = ' '; 
		return;	
	}	
		
}


/***************************************************************
*prompt
****************************************************************/
void prompt(void){
	printf("%s","wachiturrOS:~/Arqui/TP-arqui$ ");
}


