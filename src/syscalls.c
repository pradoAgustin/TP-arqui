#include "../include/kernel.h"
#include "../include/buffer.h"
#include "../include/kc.h"

int registers[20];

//preguntas

//para eflags tengo q acceder al stack(cs ip eflags) iret en la interrupcion de teclado
//shell???? separacion video y shell, diferencias
//getchar(parece demasiado simple el mio )
//int 80?
//driver de video? 
//2 buffers? 3???? ejemplo hola pepe, borra ->hola mundo
//esta bien mi acceso a registros o es un poco villero?
// pasos atapi, ingresar a todos los buses y todo los devices! ir preguntando cual es el que tiene el controlador de ata y dsp la funcionalidad del ata
// int 09 llama al writeBuffer y tmb a readBuffer o quien termina imprimiendo en pantalla
//puede ser que si tipeo rapido hay caracteres que se los saltea?
// no encuentro donde esta el cursor para q vayan los 2 a la par
//que otra opcion habria a usar cursor como variable global que no sea pasasrla por parametro??
//mis registros estan cambiando(si pongo por ejemplo un while 1 printf) pero no se si estan bien, tengo forma de comprobarlo?
//no puedo solucionar de pasarle stdout 1 y stdout2 a putchar

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

