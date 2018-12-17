#include <stdlib.h>
#include <oslib.h>
#include <uart.h>

Semaphore *mutex = NULL;

void code()
{
    int k;
    uint32 id = task_id();

    while (1)
    {

        sem_p(mutex);
        uart_printf(_UART0, "tache %d\n", id);
        sem_v(mutex);

        for (k = 0; k < 50000; k++)
            ;
    }
}

void dummy()
{
    while (1)
        ;
}

int main()
{
    mutex = sem_new(1);

    task_new(code, 256);  // tache 1
    task_new(code, 256);  // tache 2
    task_new(code, 256);  // tache 3
    task_new(code, 256);  // tache 4
    task_new(dummy, 128); // tache 5

    os_start();

    return 0;
}
