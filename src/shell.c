#include "../include/buffer.h"
buffer buf;
int echo ();
int man();
int troll();
int test1();
int opencd();
int closecd();
int infocd();
char s[20];
int i;


int shell(){
int j,a;
char c;

	while( ((c=getchar()) != 0)){
		s[i]=c;
		i++;
	putc(c,1);
	}

if(!strcmp(s,"man\n")){
	man();
}
if(!strcmp(s,"opencd\n")){
	printf("abri cd mierda");
	opencd();
}
if(!strcmp(s,"closecd\n")){
	printf("cerra cd mierda");
	closecd();
}
if(!strcmp(s,"infocd\n")){
	printf("informacion del cd mierda");
	infocd();
}

return 0;
}	

int man(){
printf("man \t muestra en pantalla todos los comandos posibles\n");
printf("opencd \t abre la disquetera\n");
printf("closecd \t cierra la disquetera\n");
printf("infoCD \t  informacion sobre el cd en la disquetera\n");
printf("test1 \t sirve para demostrar el funcionamiento de scanf, printf,\n");
printf("test2 \t muestra un cambio en los registros\n");
printf("troll \t comando sorpresa \n");


}
int troll(){



}
int test1(){



}
int opencd(){

}
int closecd(){

}
int infocd(){
	
}