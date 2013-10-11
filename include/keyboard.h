

#define ESC 1
#define INV 1

char scanCodeToASCII1[0xff] =
{    /*  0    1    2    3    4    5    6    7    8    9    A    B    C    D    E     F    */
/*0*/   INV, ESC, '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '\'', INV, '\b', '\t',
 
/*1*/   'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', INV, '+', '\n', INV, 'a', 's',
 
/*2*/   'd', 'f', 'g', 'h', 'j', 'k', 'l', INV, '{', '}', INV, '<', 'z', 'x', 'c', 'v',
 
/*3*/   'b', 'n', 'm', ',', '.', '/', INV, '*', INV, ' ', INV, 0xB3, INV, INV, INV, INV,
 
/*4*/   INV, INV, INV, INV, INV, INV, INV, '7', '8', '9', '-', '4', '5', '6', '+', '1',
 
/*5*/   '2', '3', '0', '.', INV, INV, INV, INV, INV, INV, INV, INV, INV, INV, INV, INV
 
};

/* borra */
void backspace();

/* enter */
void enter();

/* tab*/
void tab();

/*scan code to ascii translator*/
char scanCodeToASCII(char c);

