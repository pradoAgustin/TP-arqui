#include "../include/kernel.h"
#include "../include/buffer.h"

typedef struct{
        char * vec;
        int read;
        int write;
			}buffer;
buffer buf;

int initializeBuffer(){
	char vec[40];
	buf.vec=vec;
	buf.read=0;
	buf.write=0;
}
void storeInBuffer(char c){
	if(buf.write>40){
		buf.write=0;
}
	buf.vec[buf.write]=c;
	buf.write++;	
	
return;
}

char getBuffer(){
	char c;
	if(buf.read>40){
	buf.read=0;

}
	if(buf.read==buf.write){return 0;}
	c= buf.vec[buf.read];
	buf.read++;
	return c;
}



