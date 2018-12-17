#include <oslib.h>
#include <uart.h>

void code()
{
    int   k;
    uint8 id=task_id();

    while(1) {
		uart_printf(_UART0, "tache %d\n",id);
        for (k=0;k<50000;k++);
    }
}


int main()
{
    task_new(code, 256);   // tache 1
    task_new(code, 256);   // tache 2
    task_new(code, 256);   // tache 3
    task_new(code, 256);   // tache 4

    os_start();

    return 0;
}
