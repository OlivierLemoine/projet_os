#include <stdlib.h>
#include <oslib.h>
#include <lcd.h>

Semaphore *mutex;
uint8 cpt=0;
int fd0, fd1, fd2;

void tache1()
{
	lcd_clear();
    lcd_printf("t1 : cpt = %d", cpt);

	fd0=open("/dev/btn0", O_RDONLY);

    while (1) {
        int pushed;
        read(fd0,(void*)&pushed,4);
        sem_p(mutex);
        cpt=0;
   		lcd_clear();
        lcd_printf("t3 : cpt = %u", cpt);
        sem_v(mutex);
    }
}

void tache2()
{
	fd1=open("/dev/btn1", O_RDONLY);

    while (1) {
        int pushed;
        read(fd1,(void*)&pushed,4);
        sem_p(mutex);
        --cpt;
   		lcd_clear();
        lcd_printf("t2 : cpt = %u", cpt);
        sem_v(mutex);
    }
}

void tache3()
{
	fd2=open("/dev/btn4", O_RDONLY);

    while (1) {
        int pushed;
        read(fd2,(void*)&pushed,4);
        sem_p(mutex);
        ++cpt;
   		lcd_clear();
        lcd_printf("t1 : cpt = %u", cpt);
        sem_v(mutex);
    }
}

void idle()
{
    while(1) {}
}


int main()
{
	lcd_init();
	lcd_display(LCD_DISPLAY_DISPLAY_ON);
   	lcd_clear();
   	lcd_home();
   	
    mutex=sem_new(1);

    task_new(tache1,512);
    task_new(tache2,512);
    task_new(tache3,512);
    task_new(idle,4);

    os_start();

    return 0;
}
