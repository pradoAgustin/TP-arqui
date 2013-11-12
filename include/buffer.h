
void storeInBuffer(int c);
int getBuffer();

typedef struct{
        char * vec;
        int read;
        int write;
			}buffer;
buffer buf;
#define MAX_BUFFER 1024
