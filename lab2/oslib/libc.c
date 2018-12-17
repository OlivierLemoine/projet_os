#include <sys/types.h>

#include <stddef.h>
#include <stdlib.h>
#include <string.h>

char *
strdup(const char *str)
{
	size_t siz;
	char *copy;

	siz = strlen(str) + 1;
	if ((copy = malloc(siz)) == NULL)
		return(NULL);
	(void)memcpy(copy, str, siz);
	return(copy);
}
