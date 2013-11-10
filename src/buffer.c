#include "../include/kernel.h"
#include "../include/buffer.h"


void storeInBuffer(char c){
	if(buf.write==MAX_BUFFER){
		buf.write=0;
}
	buf.vec[buf.write]=c;
	buf.write++;	
	
return;
}

char getBuffer(){
	char c;
	if(buf.read>MAX_BUFFER){
		buf.read=0;
	}
	if(buf.read==buf.write){
		return 0;

	}
		c= buf.vec[buf.read];
		buf.read++;
		return c;
}
