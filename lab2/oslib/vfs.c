#include <stdlib.h>
#include <string.h>
#include <vfs.h>
#include <fat.h>

/***************************************************************************
 * File name manipulation utilities
 ***************************************************************************/
// -------------------- dirname ------------------------------------------
// returns parent's name (everything before the last '/')
char *dirname(char *path)
{
    char *dname = strdup(path);
    char *slash = NULL;
    char *p = dname;

    while (*p)
    {
        if (*p == '/')
            slash = p;
        p++;
    }

    if (slash)
        *slash = 0;
    if (*dname == 0)
        strcpy(dname, "/");
    return dname;
}

// -------------------- basename ------------------------------------------
// returns the filename (everything after the last '/')
char *basename(char *path)
{
    char *p = path;
    char *slash = NULL;
    while (*p)
    {
        if (*p == '/')
            slash = p;
        p++;
    }
    if (slash)
        return slash + 1;
    else
        return path;
}

/***************************************************************************
 * Opened file descriptor array with Device associated to file descriptor
 ***************************************************************************/
FileObject *opened_fds[MAX_OPENED_FDS];

/***************************************************************************
 * Registered device table
 ***************************************************************************/
extern Device *device_table[];
extern Device dev_fs;
extern Device dev_test;

/* dev_lookup
 *   search for a device represented by its name in the device table
 */
static Device *dev_lookup(char *path)
{
    char *dir = dirname(path);

    if (!strcmp(dir, "/dev"))
    {
        free(dir);
        int i = 0;
        char *devname = basename(path);

        Device *dev = device_table[0];
        while (dev)
        {
            if (!strcmp(devname, dev->name))
                return dev;
            dev = device_table[++i];
        }
    }
    else
        free(dir);
    return NULL;
}

/***************************************************************************
 * FAT Object
 ***************************************************************************/

int mount()
{
    return dev_fs.init(&dev_fs);
}

/***************************************************************************
 * Generic device functions
 ***************************************************************************/

/* open
 *   returns a file descriptor for path name
 */
int open(char *path, int flags)
{

    FileObject **fo = opened_fds;

    while ((*fo) != NULL)
    {
        fo++;
        if (fo >= MAX_OPENED_FDS + opened_fds)
            return -1;
    }

    *fo = malloc(sizeof(FileObject));

    (*fo)->name = basename(path);
    (*fo)->file = NULL;
    (*fo)->dir = NULL;
    (*fo)->offset = 0;
    (*fo)->flags = flags;

    if (strcmp(path, "/dev") == 0)
    {
        (*fo)->flags |= F_IS_DEVDIR;
        return ((int)fo - (int)opened_fds) / 4;
    }

    (*fo)->dev = dev_lookup(path);

    if ((*fo)->dev)
    {
        if ((*fo)->dev->open)
            (*fo)->dev->open(*fo);
        return ((int)fo - (int)opened_fds) / 4;
    }
    else
    {
        (*fo)->name = path;
        (*fo)->dev = &dev_fs;
        if ((*fo)->dev->open)
            if((*fo)->dev->open(*fo))
                return ((int)fo - (int)opened_fds) / 4;
    }

    free(*fo);
    return -1;
}

/* close
 *   close the file descriptor
 */
int close(int fd)
{
    FileObject *fo = opened_fds[fd];
    if (fo->dev->close)
        if (fo->dev->close(fo))
        {
            free(fo);
            return 0;
        }
    return -1;
}

/* read
 *   read len bytes from fd to buf, returns actually read bytes
 */
int read(int fd, void *buf, size_t len)
{
    FileObject *fo = opened_fds[fd];
    if (fo->dev->read)
        return fo->dev->read(fo, buf, len);
    return -1;
}

/* write
 *   write len bytes from buf to fd, returns actually written bytes
 */
int write(int fd, void *buf, size_t len)
{
    FileObject *fo = opened_fds[fd];
    if (fo->dev->write)
        return fo->dev->write(fo, buf, len);
    return -1;
}

/* ioctl
 *   set/get parameter for fd
 */
int ioctl(int fd, int op, void **data)
{
    FileObject *fo = opened_fds[fd];
    if (fo->dev->ioctl)
        return fo->dev->ioctl(fo, op, data);
    return -1;
}

/* lseek
 *   set the offset in fd
 */
int lseek(int fd, unsigned int offset)
{
    FileObject *f = opened_fds[fd];
    if (f)
    {
        f->offset = offset;
        return 0;
    }
    return -1;
}

/***************************************************************************
 * Directory handling functions
 ***************************************************************************/
int dev_fs_next_dir(DIR *dir);

int readdir(int fd, DIR **dir)
{
    FileObject *f = opened_fds[fd];

    if (f)
    {
        if (f->flags & F_IS_ROOTDIR)
        {
            f->flags &= ~F_IS_ROOTDIR;
            strcpy(f->dir->entry, "dev");
            f->dir->entry_isdir = 1;
            f->dir->entry_size = 0;
            *dir = f->dir;
            return 0;
        }
        else if (f->flags & F_IS_DEVDIR)
        {
            if (device_table[f->offset])
            {
                strcpy(f->dir->entry, device_table[f->offset]->name);
                f->dir->entry_isdir = 0;
                f->dir->entry_size = 0;
                *dir = f->dir;
                f->offset++;
                return 0;
            }
        }
        else if ((f->flags & F_IS_DIR) && dev_fs_next_dir(f->dir))
        {
            *dir = f->dir;
            return 0;
        }
    }
    return -1;
}
