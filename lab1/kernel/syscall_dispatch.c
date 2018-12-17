#include "oslib.h"
#include "alloc.h"
#include "kernel.h"

/* sys_add
 *   test function
 */
int sys_add(int a, int b)
{
    return a + b;
}

/* syscall_dispatch
 *   dispatch syscalls
 *   n      : syscall number
 *   args[] : array of the parameters (4 max)
 */
int32 syscall_dispatch(uint32 n, uint32 args[])
{
    switch (n)
    {
    case 0:
        return sys_add((int)args[0], (int)args[1]);
    case 1:
        return sys_alloc((int)args[0]);
    case 2:
        return sys_free((void *)args[0]);
    case 3:
        return sys_os_start();
    case 4:
        return sys_task_new((TaskCode)args[0], (uint32)args[1]);
    case 5:
        return sys_task_id();
    case 6:
        return sys_task_wait((int)args[0]);
    case 7:
        return sys_sem_new((int)args[0]);
    case 8:
        return sys_sem_p((Semaphore *)args[0]);
    case 9:
        return sys_sem_v((Semaphore *)args[0]);
    case 10:
        return sys_task_kill();
    // case 11:
    //     return sys_mb_new((int)args[0]);
    }
    return -1;
}
