
#include <oslib.h>

// pour tester
//
int test_add(int a, int b)
{
    int val;
    asm("swi 0\n\tmov %0,r0"
        : "=r"(val));
    return val;
}

/*****************************************************************************
 * Memory allocation functions
 *****************************************************************************/
/* malloc
 *   memory allocation
 */
void *malloc(unsigned int req)
{
    void *val;
    asm("swi 1\n\tmov %0,r0"
        : "=r"(val));
    return val;
}

/* free
 *   memory free
 */
void free(void *ptr)
{
    asm("swi 2");
}

/*****************************************************************************
 * General OS handling functions
 *****************************************************************************/

/* os_start
 *   start the first created task
 */
void os_start()
{
    asm("swi 3");
}

/*****************************************************************************
 * Task handling functions
 *****************************************************************************/

/* task_new
 *   create a new task :
 *   func      : task code to be run
 *   stacksize : task stack size
 *   returns the task id
 */
int32 task_new(TaskCode func, uint32 stacksize)
{
    int val;
    asm("swi 4\n\tmov %0,r0"
        : "=r"(val));
    return val;
}

/* task_id
 *   returns id of task
 */
uint32 task_id()
{
    uint32 val;
    asm("swi 5\n\tmov %0,r0"
        : "=r"(val));
    return val;
}

/* task_kill
 *   kill oneself
 */
void task_kill()
{
    asm("swi 10");
}

/* task_wait
 *   suspend the current task until timeout
 */
void task_wait(uint32 ms)
{
    asm("swi 6");
}

/*****************************************************************************
 * Semaphore handling functions
 *****************************************************************************/

/* sem_new
 *   create a semaphore
 *   init    : initial value
 */
Semaphore *sem_new(int32 init)
{
    Semaphore *val;
    asm("swi 7\n\tmov %0,r0"
        : "=r"(val));
    return val;
}

/* sem_p
 *   take a semaphore
 */
void sem_p(Semaphore *sem)
{
    asm("swi 8");
}

/* sem_v
 *   release a semaphore
 */
void sem_v(Semaphore *sem)
{
    asm("swi 9");
}

/*****************************************************************************
 * msg
 *****************************************************************************/

MailBox *mb_new(int32 mb_size)
{
    MailBox *val;
    asm("swi 11\n\tmov %0,r0"
        : "=r"(val));
    return val;
}