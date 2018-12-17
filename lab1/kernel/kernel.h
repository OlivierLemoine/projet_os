#ifndef _KERNEL_H_
#define _KERNEL_H_

#include "typedefs.h"

typedef struct _Context
{
    uint32 r[16];
    uint32 cpsr;
} Context;

extern Context *saved_ctx;

typedef enum
{
    TASK_RUNNING,
    TASK_READY,
    TASK_SLEEPING,
    TASK_WAITING
} TaskState;

typedef struct _Task
{
    struct _Task *prev; // previous task in the list
    struct _Task *next; // next task in the list
    uint32 id;          // id
    TaskState status;   // task state
    uint8 *stack_base;  // base stack address
    Context ctx;        // register context : r[0] -> r0, ... r[15] + cpsr
    int32 delay;        // sleeping delay
} Task;

typedef struct _MailBox
{
    Mail *msg;
    int msg_max;
    int current_msg;
    Task *empty_waiting;
    Task *full_waiting;
} MailBox;

typedef struct _Mail
{
    void *msg;
    Mail *next;
} Mail;

/* sys_round_robin
 *   change context to next task in the ready list
 */
void sys_round_robin();

/*****************************************************************************
 * General OS handling functions
 *****************************************************************************/

#ifndef _OSLIB_H_
/* task code type
 */
typedef void (*TaskCode)();
#endif

/* sys_os_start
 *   start the first created task
 */
int32 sys_os_start();

void sys_wait();

/*****************************************************************************
 * Task handling functions
 *****************************************************************************/

/* sys_task_new
 *   create a new task :
 *   func      : task code to be run
 *   stacksize : task stack size
 */
int32 sys_task_new(TaskCode func, uint32 stacksize);

/* sys_task_kill
 *   kill oneself
 */
int32 sys_task_kill();

/* sys_task_id
 *   returns id of task
 */
int32 sys_task_id();

/* sys_task_yield
 *   run scheduler to switch to another task
 */
int32 sys_task_yield();

/* task_wait
 *   suspend the current task until timeout
 */
int32 sys_task_wait(uint32 ms);

/*****************************************************************************
 * Semaphore handling functions
 *****************************************************************************/
#ifndef _OSLIB_H_
typedef struct _Semaphore Semaphore;
#endif

struct _Semaphore
{
    int32 count;
    Task *waiting;
};

/* sys_sem_new
 *   create a semaphore
 *   init    : initial value
 */
Semaphore *sys_sem_new(int32 init);

/* sys_sem_p
 *   take a semaphore
 */
int32 sys_sem_p(Semaphore *sem);

/* sys_sem_v
 *   release a semaphore
 */
int32 sys_sem_v(Semaphore *sem);

MailBox *sys_mb_new(int32 mb_size);

#endif
