#include "../include/kernel.h"
#include "../include/buffer.h"
buffer buf;
#define MAX_BUFFER 256
int initializeBuffer(){
	char vec[MAX_BUFFER];
	buf.vec=vec;
	buf.read=0;
	buf.write=0;
	
}
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
void vacia_buffer(){buf.read=buf.write;}