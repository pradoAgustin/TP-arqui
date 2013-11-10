extern char read();
#include "../include/defs.h"
#include "../include/keyboard.h"
#include "../include/buffer.h"


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
	if(cursor > 78*25*2){
		k_scroll();//scrolleo 
		cursor=160*9;	
		printf("________________________________________________________________________________");
		cursor=160*24;
	}else
	cursor += 160 - cursor%160;
	prompt();
}
 
/***************************************************************
*Tab
****************************************************************/
void tab(){
	cursor += TAB-(cursor%4);
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
	if(puedeBorrar || !prompt2){			
		cursor -=2;
		char* videomem = (char *)(POSITION + cursor) ;
		videomem[0] = ' '; 
		update_cursor();
		return;	
	}	
		
}

/***************************************************************
*prompt
****************************************************************/
void prompt(void){
	printf("%s","wachiturrOS: ");
	prompt2=1;
}

