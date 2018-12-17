#include <target.h>

#include <stdlib.h>

#include "alloc.h"
#include "kernel.h"
#include "list.h"

#ifndef NULL
#define NULL 0
#endif

/*****************************************************************************
 * Global variables
 *****************************************************************************/

static uint32 id = 1;
Task *tsk_running = NULL;  /* pointer to ready task list : the first
                                     node is the running task descriptor */
Task *tsk_sleeping = NULL; /* pointer to sleeping task list */
Context *saved_ctx = NULL; /* pointer to current saved context on svc/irq
                                     stack */
/*****************************************************************************
 * Round robin algorithm
 *****************************************************************************/

/* sys_round_robin
 *   change context to next task in the ready list
 */
void sys_round_robin()
{
    tsk_running->ctx = *saved_ctx;
    tsk_running->status = TASK_READY;

    tsk_running = tsk_running->next;

    tsk_running->status = TASK_RUNNING;
    *saved_ctx = tsk_running->ctx;

    // list_display(tsk_running);
}

void sys_wait()
{
    for (size_t i = 0; i < list_size(tsk_sleeping); i++)
    {
        tsk_sleeping->delay -= SYS_TICK;
        if (tsk_sleeping->delay < 0)
        {
            tsk_sleeping->status = TASK_READY;
            Task **tmp_tsk;
            tsk_sleeping = list_remove_head(tsk_sleeping, tmp_tsk);
            tsk_running = list_insert_tail(tsk_running, *tmp_tsk);
        }
        else
            tsk_sleeping = tsk_sleeping->next;
    }
}

/*****************************************************************************
 * General OS handling functions
 *****************************************************************************/

/* sys_os_start
 *   start the first created task
 */
int32 sys_os_start()
{
    sys_timer_start();
    tsk_running->status = TASK_RUNNING;
    *saved_ctx = tsk_running->ctx;
    return 1;
}

/*****************************************************************************
 * Task handling functions
 *****************************************************************************/
void task_kill();

/* sys_task_new
 *   create a new task :
 *   tc        : task code to be run
 *   stacksize : task stack size
 */
int32 sys_task_new(TaskCode func, uint32 stacksize)
{
    Task *newTask = sys_alloc(sizeof(Task));
    if (newTask == NULL)
        return 0;
    newTask->stack_base = sys_alloc(stacksize);
    if (newTask->stack_base == NULL)
        return 0;

    newTask->id = id++;
    newTask->status = TASK_READY;
    newTask->ctx.cpsr = 0x10;

    for (size_t i = 0; i < 13; i++)
    {
        newTask->ctx.r[i] = 0;
    }

    newTask->ctx.r[13] = newTask->stack_base + stacksize;
    newTask->ctx.r[14] = task_kill;
    newTask->ctx.r[15] = func;
    tsk_running = list_insert_tail(tsk_running, newTask);
    return newTask->id;
}

/* sys_task_kill
 *   kill oneself
 */
int32 sys_task_kill()
{
    Task **tmp_task;

    tsk_running = list_remove_head(tsk_running, tmp_task);

    sys_free((*tmp_task)->stack_base);
    sys_free(*tmp_task);

    tsk_running->status = TASK_RUNNING;
    *saved_ctx = tsk_running->ctx;

    return 0;
}

/* sys_task_id
 *   returns id of task
 */
int32 sys_task_id()
{
    return tsk_running->id;
}

/* task_wait
 *   suspend the current task until timeout
 */
int32 sys_task_wait(uint32 ms)
{
    tsk_running->ctx = *saved_ctx;
    tsk_running->status = TASK_SLEEPING;
    tsk_running->delay = ms;

    Task **tmp_tsk;

    tsk_running = list_remove_head(tsk_running, tmp_tsk);
    tsk_sleeping = list_insert_tail(tsk_sleeping, *tmp_tsk);

    tsk_running->status = TASK_RUNNING;
    *saved_ctx = tsk_running->ctx;

    return 0;
}

/*****************************************************************************
 * Semaphore handling functions
 *****************************************************************************/

/* sys_sem_new
 *   create a semaphore
 *   init    : initial value
 */
Semaphore *sys_sem_new(int32 init)
{
    Semaphore *sem = sys_alloc(sizeof(Semaphore));
    sem->count = init;
    sem->waiting = NULL;
    return sem;
}

/* sys_sem_p
 *   take a semaphore
 */
int32 sys_sem_p(Semaphore *sem)
{
    sem->count--;

    if (sem->count < 0)
    {
        tsk_running->ctx = *saved_ctx;
        tsk_running->status = TASK_WAITING;

        Task **tmp_tsk;

        tsk_running = list_remove_head(tsk_running, tmp_tsk);
        sem->waiting = list_insert_tail(sem->waiting, *tmp_tsk);

        tsk_running->status = TASK_RUNNING;
        *saved_ctx = tsk_running->ctx;
    }

    return 0;
}

/* sys_sem_v
 *   release a semaphore
 */
int32 sys_sem_v(Semaphore *sem)
{
    sem->count++;

    if (list_size(sem->waiting) > 0)
    {
        sem->waiting->status = TASK_READY;
        Task **tmp_tsk;
        sem->waiting = list_remove_head(sem->waiting, tmp_tsk);
        tsk_running = list_insert_tail(tsk_running, *tmp_tsk);
    }

    return 0;
}

/*****************************************************************************
 * Message
 *****************************************************************************/

// MailBox *sys_mb_new(int32 mb_size)
// {
//     MailBox *mb = sys_alloc(sizeof(MailBox));
//     mb->empty_waiting = NULL;
//     mb->full_waiting = NULL;
//     mb->msg_max = mb_size;
//     mb->current_msg = 0;
//     mb->msg = NULL;
//     return mb;
// }

// int32 sys_mb_send(MailBox *mb, int *msg)
// {
//     if (mb->current_msg == mb->msg_max)
//     {
//         tsk_running->ctx = *saved_ctx;
//         tsk_running->status = TASK_WAITING;

//         Task **tmp_tsk;

//         tsk_running = list_remove_head(tsk_running, tmp_tsk);
//         mb->full_waiting = list_insert_tail(mb->full_waiting, *tmp_tsk);

//         tsk_running->status = TASK_RUNNING;
//         *saved_ctx = tsk_running->ctx;
//     }
//     else
//     {
//         Mail *myMail;
//         myMail->msg = msg;
//         myMail->next = NULL;

//         Mail *mail_ptr = mb->current_msg;

//         while (mail_ptr != NULL)
//             mail_ptr = mail_ptr->next;

//         if (mail_ptr == NULL)
//             mb->msg = myMail;
//         else
//             mail_ptr->next = myMail;

//         mb->current_msg++;

//         if (mb->empty_waiting != NULL)
//         {
//             mb->empty_waiting->status = TASK_READY;
//             Task *tmp_tsk;
//             mb->empty_waiting = list_remove_head(mb->empty_waiting, &tmp_tsk);
//             tsk_running = list_insert_tail(tsk_running, tmp_tsk);

//             tmp_tsk->ctx.r[2] = mb->msg->msg;
//             mb->msg = mb->msg->next;
//         }
//     }
// }

// int32 sys_mb_recv(MailBox *mb, int *msg)
// {
//     if (mb->current_msg == 0)
//     {
//         tsk_running->ctx = *saved_ctx;
//         tsk_running->status = TASK_WAITING;

//         Task **tmp_tsk;

//         tsk_running = list_remove_head(tsk_running, tmp_tsk);
//         mb->empty_waiting = list_insert_tail(mb->empty_waiting, *tmp_tsk);

//         tsk_running->status = TASK_RUNNING;
//         *saved_ctx = tsk_running->ctx;
//     }
//     else
//     {
//     }
// }