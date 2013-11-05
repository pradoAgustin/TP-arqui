
int fillBuffer();
//void readBuffer();
void writeBuffer();
void storeInBuffer(char c);
char getBuffer();

typedef struct{
        char * vec;
        int read;
        int write;
			}buffer;


