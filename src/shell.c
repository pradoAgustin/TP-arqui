#include "../include/buffer.h"
buffer buf;
int echo ();
int man();
int troll();
int test1();
int opencd();
int closecd();
int infocd();
void testuno();
void testdos();
int cursor;
extern _opencd();
extern _printError();
extern _cambiar_registros();
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
			printf("Abriendo cd :) \n");
			opencd();
		}
		if(!strcmp(s,"closecd")){
			printf("Cerrando cd :)\n");
			closecd();
		}
		if(!strcmp(s,"testuno")){
			testuno();
		}
		if(!strcmp(s,"infocd")){
			printf("Informacion del cd \n");
			infocd();
		}
		if(!strcmp(s,"clearup")){
			clearup();
		}
		if(!strcmp(s,"troll")){
			troll();
		}
		if(!strcmp(s,"testdos"))
		{
			testdos();
		}
		if(!strcmp(s,"clear")){
			clear();
		}
		//else 
			//printf("comando invalido\n");
		
return;
}	

int man(){
printf("man    \t Muestra en pantalla todos los comandos posibles\n");
printf("opencd \t Abre la disquetera\n");
printf("closecd\t Cierra la disquetera\n");
printf("infoCD \t Informacion sobre el cd en la disquetera\n");
printf("testuno\t Demostrar el funcionamiento de scanf, printf,\n");
printf("testdos\t Muestra un cambio en los registros");
printf("\n");
printf("troll  \t Comando sorpresa \n");



}
int troll(){
	cursor=0;
	k_clear_screen();
 printf("                  {}\n");
printf("  ,   A           {}\n");
printf(" / \\, | ,        .--.\n");
printf("|  =|= >        /.--.\\\n");
printf(" \\ /` | `       |====|\n");
printf("  `   |         |`::`|\n");
printf("      |     .-;`\\..../`;_.-^-._\n");
printf("     /\\\\/  /  |...::..|`   :   `|\n");
printf("     |:'\\ |   /'''::''|   .:.   |\n");
printf("      \\ /\\;-,/\\   ::  |..ASCII..|\n");
printf("      |\\ <` >  >._::_.| ':ART:' |\n");
printf("      | `""`_/   ^^/>/>  |   ':'   |\n");
printf("      |       |       \\    :   /\n");
printf("      |       |        \\   :   /\n");
printf("      |       |___/\\___|`-.:.-`\n");
printf("      |        \\_ || _/    `\n");
printf("      |        <_ >< _>\n");
printf("      |        |  ||  |\n");
printf("      |        |  ||  |\n");
printf("      |       _\\.:||:./_\n");
printf("      | jgs  /____/\\____\\\n");
printf("\n");
 }
void testuno(){
printf("Bienvenido a nuestro sistema operativo para wachiturros\n");
printf("Ingrese su nombre o tirese un paso \n");
char c;
int i=0;
char * n;
char s[20];
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

printf("Bienvenido wachiturro %s \n\n",s);
printf("Los comandos disponibles son los siguientes\n\n");
man();
}

void testdos(){
	int i = 0;
	int j = 0;
	_cambiar_registros();
	// while (i<200)
	// {
	// 	while(j<1000)
	// 	{
	// 		j++;
	// 	}
	// 	int_09(25);
	// 	i++;
	// }
	// return;


}

// void testtres(){

// }
//char * parse_name()
int clear(){
	k_clear_screen();
	initialize_screen();
}

int clearup(){
	k_clear_upper_screen();
}
int opencd(){
	_opencd();
	printf("ya esta\n");
}


int closecd(){
	_closecd();
}


int infocd(){
	_infocd();
}

int printStatus(int num){
int flag = 0;
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