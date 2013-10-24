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
*scanCodeToASCII2
****************************************************************/

char scanCodeToASCIIshifted(char c){
	return scanCodeToASCII2[c];
}


/***************************************************************
* Enter
****************************************************************/

void enter(){
	if(cursor > 75*25*2){
		k_clear_screen(); 
		cursor=160*9;	
		printf("________________________________________________________________________________");
		cursor=160*10;
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
		if(cursor==(13*2+160*i))
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
*shifted
****************************************************************/
//int shifted()








/***************************************************************
*prompt
****************************************************************/
void prompt(void){
	printf("%s","wachiturrOS: ");
}


