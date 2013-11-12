#include "../include/kernel.h"
#include "../include/buffer.h"

void storeInBuffer(int c){
	if(buf.write==MAX_BUFFER){
		buf.write=0;
}
	buf.vec[buf.write]=c;
	buf.write++;	
	
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
		buf.read=0;
		buf.write=0;
		return 0;

	}
		c= buf.vec[buf.read];
		buf.read++;
		return c;
}
