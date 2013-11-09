#include "../include/buffer.h"
buffer buf;
int echo ();
int man();
int troll();
int test1();
int opencd();
int closecd();
int infocd();
extern _opencd();
extern _printError();
void parsecommand(char * s);
extern _closecd();

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
		
	}// si atapi retorna 1 esta todo bien sino no
}
//enter();
	putc(c,1);
	s[i]='\0';

	parsecommand(s);
}
	// buf.read = buf.write;

void parsecommand(char * s)
{	
		if(!strcmp(s,"man")){
			man();
		}
		if(!strcmp(s,"opencd")){
			printf("abri cd mierda\n");
			opencd();
		}
		if(!strcmp(s,"closecd")){
			printf("cerra cd mierda\n");
			closecd();
		}
		if(!strcmp(s,"infocd")){
			printf("informacion del cd mierda\n");
			infocd();
		}
		else 
			printf("comando invalido\n");
		
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
_opencd();
printf("ya esta\n");

}
int closecd(){
	_closecd();
}

int infocd(){
	
}

int printStatus(int num){
int flag = 0;

// if((num & 0) == 0){
// printf("No flags ");
// }


if((num & 2) == 2){
printf("IDX ");
flag = 1;
}

if((num & 4) == 4){
printf("Corr ");
flag = 1;
}

if((num & 8) == 8){
printf("DRQ ");
flag = 1;
}

if((num & 16) == 16){
printf("DSC ");
flag = 1;
}

if((num & 32) == 32){
printf("DF ");
flag = 1;
}

if((num & 64) == 64){
printf("DRDY ");
flag = 1;
}

if((num & 128) == 128){
printf("BSY ");
flag = 1;
}

if(flag == 0){
printf("No flags ");
}

if((num & 1) == 1){
printf("Error: ");
_printError();

flag = 1;
}

printf("\n");



return 0;
}

int printNum(int num){
	printf("%d",num);
}

//mkiso