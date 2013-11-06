#include "../include/buffer.h"
buffer buf;
int echo ();
int man();
int troll();
int test1();
int opencd();
int closecd();
int infocd();


void parsecommand(char * s);

void shell(){
char s[20];
int i=0;
int j,a;

char c;
	while( ((c=getchar()) != '\n')){
		if(c!=0){
			if(c == '\b' && i >= 1){
			i--;
			putc(c ,1);
		}
		if(c != '\b' && c!='\n')
		{
			s[i] = c;
			i++;
			putc(c ,1);
			
		}
		
	}
}
	putc(c,1);
	s[i]='\0';
	parsecommand(s);
}
	//buf.read=buf.write;

void parsecommand(char * s)
{	
		if(!strcmp(s,"man")){
			man();
		}
		if(!strcmp(s,"opencd")){
			printf("abri cd mierda");
			opencd();
		}
		if(!strcmp(s,"closecd")){
			printf("cerra cd mierda");
			closecd();
		}
		if(!strcmp(s,"infocd")){
			printf("informacion del cd mierda");
			infocd();
		}
		
return;
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