#ifndef _EINT_H_
#define _EINT_H_

#include "board.h"

typedef void (*OnEint)(void);

#define EXT_EINT0_BIT			0
#define EXT_EINT1_BIT			1
#define EXT_EINT2_BIT			2
#define EXT_EINT3_BIT			3

#define EXT_LEVEL_SENSITIVE		0
#define EXT_EDGE_SENSITIVE		1
#define EXT_LOW					0
#define EXT_HIGH				1
#define EXT_FALLING				0
#define EXT_RISING				1

/* eint1_init
 *   mode   : EXT_LEVEL_SENSITIVE / EXT_EDGE_SENSITIVE
 *   polar  : EXT_LOW / EXT_HIGH or EXT_FALLING / EXT_RISING
 *   cb     : callback on pushed button event
 */
void eint1_init(uint32 mode, uint32 polar, OnEint cb);

#endif
