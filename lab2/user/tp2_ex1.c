#include <stdlib.h>
#include <oslib.h>
#include <uart.h>

char buffer[32];
int fd;

void tache1()
{
	int n, i;
	
	fd=open("/dev/test", O_READ);
	if (fd!=-1) {
		// lseek(fd,5);
		n=read(fd, buffer, 32);
		
		for(i=0;i<n;i++) uart_putc(_UART0, buffer[i]);
		
		close(fd);
	}

	while (1) { }
}

void idle()
{
    while (1) { }
}

int main()
{
    task_new(tache1,256);
    task_new(idle,4);

    os_start();

    return 0;
}
