#include "../include/kernel.h"
#include "../include/buffer.h"
extern _iniciar_contador();

void storeInBuffer(int c){
	if(buf.write==MAX_BUFFER){
		buf.write=0;
}
	buf.vec[buf.write]=c;
	buf.write++;
	_iniciar_contador();	
return;
}
void initializeBuffer(){
buf.read=0;
buf.write=0;
}


int getBuffer(){
	int c;
	if(buf.read>MAX_BUFFER){
		buf.read=0;
	}
	if(buf.read==buf.write){
	initializeBuffer();
		return 0;

	}
		c= buf.vec[buf.read];
		buf.read++;
		return c;
}
// eax es 1 si getchar devuelve enter
// eax es 0 si getchar devuelve distinto enter
// ebx lo que yo quiera xq el sistema no lo usa
// ecx strmcmp o lo que querramos 
// edx read o write del buffer