#include <stdlib.h>
#include <oslib.h>
#include <uart.h>
#include <io.h>

Semaphore * sem=NULL;
int cpt=0;


void tache1()
{
    while (1) {
        sem_p(sem);
        uart_printf(_UART0, "tache 1 : cpt = %d\n",++cpt);
    }
}

void tache2()
{
    while (1) {
    	if (button0()) {
    		sem_v(sem);
    	}
    	volatile int k;
    	for (k=0;k<1000;k++) ;
    }
}

int main()
{
    sem = sem_new(0);

    task_new(tache1, 256);
    task_new(tache2, 256);

    os_start();

    return 0;
}
