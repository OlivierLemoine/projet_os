#include <stdlib.h>
#include <oslib.h>


void tache1()
{
    uint8 cpt=0;

    int lfd=open("/dev/leds",O_WRONLY);

    int bfd=open("/dev/p014", O_RDONLY);

    while (1) {
        int pushed;
        read(bfd,(void*)&pushed,4);    // bloque la tache jusqu'à l'appui sur p0.14
        cpt++;
        write(lfd,&cpt,1);
    }
}


void idle()
{
    while(1) {}
}


int main()
{
    task_new(tache1,512);
    task_new(idle,128);

    os_start();

    return 0;
}
