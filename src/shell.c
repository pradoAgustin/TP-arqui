#include "../include/buffer.h"
#include "../include/defs.h"
#include "../include/shell.h"
extern _opencd();
extern _printError();
extern _delay();
extern _iniciar_contador();
extern _contar_caracteres();
extern _closecd();
<<<<<<< HEAD
//extern _opencd_puerto2();

=======
extern _cuenta_super_complicada();
void testscanf(void);
>>>>>>> 51f370a467c3cbfa2ac9d545dfcb3a06fa215e94
void shell(){
char s[20];
char lista[20][20];
int i=0;
int c;
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
		if(!strcmp(s,"testtres"))
		{
			testtres();
		}
		if(!strcmp(s,"clear")){
			clear();
		}
		if(!strcmp(s,"testscanf")){
		testscanf();
		}
		if(!strcmp(s,"cleardown")){
		clear_down();
		}
return;
}	

int man(){
printf("man    \t Muestra en pantalla todos los comandos posibles\n");
printf("opencd \t Abre la disquetera\n");
printf("closecd\t Cierra la disquetera\n");
printf("infoCD \t Informacion sobre el cd en la disquetera\n");
printf("test1\t Demostrar el funcionamiento de scanf, printf,\n");
printf("test2\t Test sobre los registros\n");
printf("test3\t Mas tests sobre los registros\n");
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
printf("      \\ /\\;-,/\\   ::  |..ARQUI..|\n");
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
printf("      |      /____/\\____\\\n");
printf("\n");

{int i=0;
 while(i<90000000){i++;}}
 initialize_screen();
 }

void testuno(){
printf("Bienvenido a nuestro sistema operativo para wachiturros\n");
printf("Ingrese su nombre o tirese un paso \n");

testscanf();

man();

return;
}

void testdos(){
	int i = 0;
	_iniciar_contador();
	while (i<1300)
	{
		_delay();
		_contar_caracteres();
		putc(25,1);
		i++;
	}
	return;
}

void testtres(){
	int i = 0;
	int result = 0;
	_iniciar_contador();
	while (i<1500)
	{
		_delay();
		result = _cuenta_super_complicada();
		printf("%s","se esta ejecutando un calculo de alta complejidad, apretar ctrl+r para ver el resultado en ECX(el resultado varia con la espera)" );
		i++;
	}
	printf("\n");
	printf("%d\n", result);
	return;
}

void testscanf(void){
char c;
char d[20];

	scanf("%s",d);
	printf("\nBienvenido wachiturro %s\n\n",d);
}
void clear_down(void){
k_clear_screen2();
initialize_screen();
}


int clear(){
	k_clear_screen();
	initialize_screen();
}

int clearup(){
	k_clear_upper_screen();
}

int opencd(){
	_opencd();
	//_opencd_puerto2();
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

void printCapacity(unsigned int lba){
    printf("Capacity = %d", (lba+1)*2000);
}

void printReady()
{
	printf("%s\n", "disk ready" );
	return;
}

void printbusy()
{
	printf("%s\n", "disk busy" );
	return;
}
