#include <stdlib.h>
#include <oslib.h>
#include <uart.h>
#include <io.h>

Semaphore * mutex=NULL;


void tache1()
{
    uint8 id=task_id();

    while (1) {
        sem_p(mutex);
        uart_printf(_UART0, "- tache %d\n", id);
        sem_v(mutex);
        leds(0);			// toggle power led
        task_wait(1500);
        leds(1);			// toggle power led
        task_wait(1500);
    }
}

void tache2()
{
    uint8 id=task_id();

    while (1) {
        sem_p(mutex);
        uart_printf(_UART0, "tache %d\n", id);
        sem_v(mutex);
        task_wait(500);
    }
}

void tache3()
{
    while(1) { }
}


int main()
{
    mutex=sem_new(1);

    task_new(tache1, 256);
    task_new(tache2, 256);
    task_new(tache3, 128);

    os_start();

    return 0;
}
