#include <stdlib.h>
#include <board.h>
#include <io.h>
#include <irq.h>
#include <uart.h>
#include <eint.h>
#include <timer.h>
#include <i2c.h>
#include <diskio.h>
#include <fat.h>
#include "target.h"

#include <vfs.h>

#ifndef __WITH_GPIO_DEV
#define __WITH_GPIO_DEV 1
#endif

/***************************************************************************
 * external symbols
 ***************************************************************************/
extern FileObject *opened_fds[]; /* oslib/device.c  */
void sys_round_robin();          /* kernel/kernel.c */
void sys_sem_v(Semaphore *s);    /* kernel/kernel.c */
void minit();                    /* kernel/alloc.c */

/***************************************************************************
 * test device driver
 ***************************************************************************/
static int dev_init_test(Device *dev);
static int dev_open_test(FileObject *f);
static int dev_close_test(FileObject *f);
static int dev_read_test(FileObject *f, void *buf, size_t len);

Device dev_test = {
    .name = "test",
    .refcnt = 0,
    .sem_read = NULL,
    .sem_write = NULL,
    .init = dev_init_test,
    .open = dev_open_test,
    .close = dev_close_test,
    .read = dev_read_test,
    .write = NULL,
    .ioctl = NULL};

static int dev_init_test(Device *dev)
{
    dev->mutex = sem_new(1);
    if (dev->mutex)
        return 1;
    return 0;
}

static int dev_open_test(FileObject *f)
{
    sem_p(f->dev->mutex);
    if (f->flags & (O_READ))
    {
        f->dev->refcnt++;
        sem_v(f->dev->mutex);
        return 1;
    }
    sem_v(f->dev->mutex);
    return 0;
}

static int dev_close_test(FileObject *f)
{
    sem_p(f->dev->mutex);
    f->dev->refcnt--;
    sem_v(f->dev->mutex);
    return 1;
}

static int dev_read_test(FileObject *f, void *buf, size_t len)
{
    int n;
    char *file = "ceci est un test\n";
    sem_p(f->dev->mutex);
    // calculate max available readable data length
    n = f->offset < strlen(file) ? strlen(file) - f->offset : 0;
    // actually, we have to read the min from available length and expected length
    n = n < len ? n : len;
    memcpy(buf, file + f->offset, n);
    f->offset += n;
    sem_v(f->dev->mutex);
    return n;
}

#ifdef __WITH_GPIO_DEV

/***************************************************************************
 * leds device driver
 ***************************************************************************/
static int dev_init_leds(Device *dev);
static int dev_open_leds(FileObject *f);
static int dev_close_leds(FileObject *f);
static int dev_write_leds(FileObject *f, void *buf, size_t len);

Device dev_leds = {
    .name = "leds",
    .refcnt = 0,
    .sem_read = NULL,
    .sem_write = NULL,
    .init = dev_init_leds,
    .open = dev_open_leds,
    .close = dev_close_leds,
    .read = NULL,
    .write = dev_write_leds,
    .ioctl = NULL};

static int dev_init_leds(Device *dev)
{
    dev->mutex = sem_new(1);
    return 1;
}

static int dev_open_leds(FileObject *f)
{
    sem_p(f->dev->mutex);
    if (f->dev->refcnt || (f->flags & (O_READ | O_NONBLOCK | O_APPEND | O_SHLOCK | O_EXLOCK | O_ASYNC | O_SYNC | O_CREAT | O_TRUNC | O_EXCL)))
        goto err;
    if (f->flags & O_WRITE)
    {
        f->dev->refcnt++;
        // P0.8:15 -> output (leds)
        io_configure(IO_PORT0, 0x00000F00, IO_PIN_OUTPUT);
        leds(0);
        sem_v(f->dev->mutex);
        return 1;
    }
err:
    sem_v(f->dev->mutex);
    return 0;
}

static int dev_close_leds(FileObject *f)
{
    sem_p(f->dev->mutex);
    f->dev->refcnt--;
    sem_v(f->dev->mutex);
    return 1;
}

static int dev_write_leds(FileObject *f, void *buf, size_t len)
{
    sem_p(f->dev->mutex);

    leds(*(uint8 *)buf);

    sem_v(f->dev->mutex);

    return 1;
}

/***************************************************************************
 * EINT1 External Interrupt Button device driver
 ***************************************************************************/
static int dev_init_btn(Device *dev);
static int dev_open_btn(FileObject *f);
static int dev_close_btn(FileObject *f);
static int dev_read_btn(FileObject *f, void *buf, size_t len);

Device dev_eint1 = {
    .name = "p014",
    .refcnt = 0,
    .init = dev_init_btn,
};

/*
 *  ISR callback (IRQ mode !!)
 */
static void on_button_cb()
{
    sys_sem_v(dev_eint1.sem_read);
}

static int dev_init_btn(Device *dev)
{
    eint1_init(EXT_EDGE_SENSITIVE, EXT_RISING, on_button_cb);
    dev->sem_read = sem_new(0);
    dev->read = dev_read_btn;
    return 1;
}

static int dev_open_btn(FileObject *f)
{
    sem_p(f->dev->mutex);
    if (f->dev->refcnt || (f->flags & (O_WRITE | O_NONBLOCK | O_APPEND | O_SHLOCK | O_EXLOCK | O_ASYNC | O_SYNC | O_CREAT | O_TRUNC | O_EXCL)))
        goto err;
    if (f->flags & O_READ)
    {
        f->dev->refcnt++;
        sem_v(f->dev->mutex);
        return 1;
    }
err:
    sem_v(f->dev->mutex);
    return 0;
}

static int dev_close_btn(FileObject *f)
{
    sem_p(f->dev->mutex);
    f->dev->refcnt--;
    sem_v(f->dev->mutex);
    return 1;
}

static int dev_read_btn(FileObject *f, void *buf, size_t len)
{
    // free(f->dev->sem_read);
    // f->dev->sem_read = sem_new(0);
    sem_p(f->dev->sem_read);
    return 0;
}

/***************************************************************************
 * GPIO Buttons device driver
 ***************************************************************************/

static int dev_init_btns(Device *dev)
{
    // P0.16:20 -> input (push button)
    io_configure(IO_PORT0, 0x001F0000, IO_PIN_INPUT);

    dev->sem_read = sem_new(0);
    dev->read = dev_read_btn;

    return 1;
}

Device dev_btn0 = {
    .name = "btn0",
    .refcnt = 0,
    .init = dev_init_btns,
};

Device dev_btn1 = {
    .name = "btn1",
    .refcnt = 0,
    .init = dev_init_btns,
};

Device dev_btn2 = {
    .name = "btn2",
    .refcnt = 0,
    .init = dev_init_btns,
};

Device dev_btn3 = {
    .name = "btn3",
    .refcnt = 0,
    .init = dev_init_btns,
};

Device dev_btn4 = {
    .name = "btn4",
    .refcnt = 0,
    .init = dev_init_btns,
};

#endif

/***************************************************************************
 * System timer interrupt callback
 ***************************************************************************/
unsigned int tick = 0;

static void on_timeout_cb()
{
    if (tick % SYS_TICK)
    {
        sys_round_robin();

#ifdef __WITH_GPIO_DEV
        if (button0())
        {
            sys_sem_v(dev_btn0.sem_read);
        }
        else if (button1())
        {
            sys_sem_v(dev_btn1.sem_read);
        }
        else if (button2())
        {
            sys_sem_v(dev_btn2.sem_read);
        }
        else if (button3())
        {
            sys_sem_v(dev_btn3.sem_read);
        }
        else if (button4())
        {
            sys_sem_v(dev_btn4.sem_read);
        }
#endif
    }
    disk_timerproc();
    tick++;
}

/***************************************************************************
 * RS232 device driver
 ***************************************************************************/

static int dev_init_console(Device *dev);
static int dev_open_console(FileObject *f);
static int dev_close_console(FileObject *f);
static int dev_write_console(FileObject *f, void *buf, size_t len);
static int dev_read_console(FileObject *f, void *buf, size_t len);

Device dev_console = {
    .name = "console",
    .refcnt = 0,
    .init = dev_init_console,
};

// called from the ISR for each received char
static void on_receive_cb()
{
    sys_sem_v(dev_console.sem_read);
}

static int dev_init_console(Device *dev)
{
    uart_init(_UART0, 115200, UART_8N1, on_receive_cb);

    dev->sem_read = sem_new(0);

    dev->open = dev_open_console;
    dev->read = dev_read_console;
    dev->write = dev_write_console;

    return 1;
}

static int dev_open_console(FileObject *f)
{
    sem_p(f->dev->mutex);
    if (f->dev->refcnt || (f->flags & (O_NONBLOCK | O_APPEND | O_SHLOCK | O_EXLOCK | O_ASYNC | O_SYNC | O_CREAT | O_TRUNC | O_EXCL)))
        goto err;
    if (f->flags & (O_READ | O_WRITE))
    {
        f->dev->refcnt++;
        sem_v(f->dev->mutex);
        return 1;
    }
err:
    sem_v(f->dev->mutex);
    return 0;
}

static int dev_close_console(FileObject *f)
{
    sem_p(f->dev->mutex);
    f->dev->refcnt--;
    sem_v(f->dev->mutex);
    return 1;
}

static int dev_write_console(FileObject *f, void *buf, size_t len)
{
    size_t i = 0;
    while (i < len)
    {
        uart_putc(_UART0, ((char *)(buf))[i++]);
        return 0;
    }

    return 0;
}

static int dev_read_console(FileObject *f, void *buf, size_t len)
{
    size_t i = 0;
    while (i < len)
    {
        sem_p(f->dev->sem_read);
        if (!uart_getchar(_UART0, &buf[i++]))
            return 0;
    }

    return 1;
}

/***************************************************************************
 * Device table
 ***************************************************************************/
Device *device_table[] = {
#ifdef __WITH_GPIO_DEV
    &dev_test,
    &dev_leds,
    &dev_btn0,
    &dev_btn1,
    &dev_btn2,
    &dev_btn3,
    &dev_btn4,
    &dev_eint1,
#endif
    &dev_console,
    NULL};

/***************************************************************************
 * Target Init
 ***************************************************************************/

void dev_init()
{
    timer_tick_init(_TIMER0, 1, on_timeout_cb);
    minit();

    int i = 0;
    Device *dev = device_table[0];
    while (dev)
    {
        if (dev->init)
            dev->init(dev);
        dev = device_table[++i];
    }
    for (i = 0; i < MAX_OPENED_FDS; i++)
        opened_fds[i] = NULL;
}
