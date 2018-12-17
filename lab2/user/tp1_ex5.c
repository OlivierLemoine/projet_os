#include <stdlib.h>
#include <oslib.h>
#include <io.h>

void tache1()
{
	uint8 state=0;
	
    while (1) {
    	state=!state;
        leds(state);			// toggle led
        task_wait(200);
    }
}

void tache2()
{
    while (1) {
    }
}


int main()
{
    task_new(tache1, 256);
    task_new(tache2, 128);

    os_start();

    return 0;
}
