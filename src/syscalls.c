#include "../include/kernel.h"
#include "../include/buffer.h"
#include "../include/kc.h"


/* __write
*
* Recibe como parametros:
* - File Descriptor
* - Buffer del source
* - Cantidad
*
**/

size_t __write(int fd, char buffer, size_t count){
	int i =0;
	((char *)(POSITION+cursor))[i]=(char)buffer;
	i++;
	((char *)(POSITION+cursor))[i]=WHITE_TXT;
	i++;
	cursor+=2;
	update_cursor();
}

/* __read
*
* Recibe como parametros:
* - File Descriptor
* - Buffer a donde escribir
* - Cantidad
*
**/
size_t __read(int fd, char buffer, size_t count){
char c=getBuffer();
if(c == 0)
	return 0;
return c;
}

