#ifndef _UTIL_H_
#define _UTIL_H_

#include "board.h"

/* num2str
 *   convert a number 'number' in base 'base' to the string s (the string
 *   variable must be large enough)
 */
void num2str(char *s, unsigned int number, unsigned int base);
unsigned int str2num(char *s, unsigned base);

#endif
