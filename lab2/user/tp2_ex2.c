#include <stdlib.h>
#include <oslib.h>
#include <io.h>


Semaphore * sem;

void tache1()
{
    uint8 cpt=0;

    int fd=open("/dev/leds",O_WRITE);

    while (1) {
        sem_p(sem);
        cpt++;
        write(fd,&cpt,1);
    }
}

void tache2()
{
	int k;

    while (1) {
        if (button0()) {
          sem_v(sem);
        }
        for (k=0;k<1000;k++) ;
    }
}

void idle()
{
    while(1) {}
}


int main()
{
    sem=sem_new(0);

    task_new(tache1,256);
    task_new(tache2,256);
    task_new(idle,128);

    os_start();

    return 0;
}
