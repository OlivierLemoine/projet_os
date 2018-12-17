#include <stdlib.h>
#include <stdio.h>
#include <oslib.h>
#include <string.h>
#include <termio.h>

char buffer[50];

void tache1()
{
	int c=276;
	term_init(80,24);
	
	term_clrscr();
	
	term_gotoxy(25,5);
	term_color(CL_RED, CL_BRIGHT);
	term_printf("du texte et des nombres (%d) en couleur\n", c);
	term_color(CL_DEFAULT, CL_DEFAULT);
	while (1) {
		readline("du texte ?", buffer, 50);
		term_printf("\nle texte est : %s\n", buffer);
	}
}

void idle()
{
    while(1) {}
}


int main()
{
    task_new(tache1,256);
    task_new(idle,4);

    os_start();

    return 0;
}
