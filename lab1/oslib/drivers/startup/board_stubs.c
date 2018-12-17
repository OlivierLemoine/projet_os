#include <stdlib.h>
#include <errno.h>
#include <reent.h>

/**************************** _sbrk_r.c *********************************/
/*  Newlib support routine for memory allocation.  Simple heap expansion*/
/* for normal newlib memory allocation					*/
/************************************************************************/

	/**** Locally used variables. ****/
extern char __heap_start[];
extern char __heap_end[];

static char *heap_ptr;		/* Points to current end of the heap.	*/

/************************** _sbrk_r *************************************/
/*  Support function.  Adjusts end of heap to provide more memory to	*/
/* memory allocator. Simple and dumb with no sanity checks.		*/
/*  struct _reent *r	-- re-entrancy structure, used by newlib to 	*/
/*			support multiple threads of operation.		*/
/*  ptrdiff_t nbytes	-- number of bytes to add.			*/
/*  Returns pointer to start of new heap area.				*/
/*  Note:  This implementation is not thread safe (despite taking a	*/
/* _reent structure as a parameter).  					*/
/*  Since _s_r is not used in the current implementation, the following	*/
/* messages must be suppressed.						*/
void * _sbrk_r(struct _reent *_s_r, ptrdiff_t nbytes)
{

	if (!heap_ptr){	/*  Initialize if first time through.		*/
	 heap_ptr = __heap_start;
    }

	if ((heap_ptr+nbytes)<__heap_end) {
		char  *base;		/*  errno should be set to  ENOMEM on error	*/
		base = heap_ptr;	/*  Point to end of heap.			*/
		heap_ptr += nbytes;	/*  Increase heap.				*/
		return base;		/*  Return pointer to start of new heap area.	*/
	}

	errno = ENOMEM;
	return NULL;
}

