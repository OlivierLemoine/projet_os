#ifndef _ALLOC_H_
#define _ALLOC_H_

#include "typedefs.h"

void   minit();
void * sys_alloc(unsigned int req);
int   sys_free(void* mem);

#endif
