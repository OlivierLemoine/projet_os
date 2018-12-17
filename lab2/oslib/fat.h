#ifndef _FAT_H_
#define _FAT_H_

#include <typedefs.h>

#define MAXPATHLEN 80

typedef struct {
	uint32	part_start;
	uint32	part_size;
	uint32  csize;
	uint32	fat_start;
	uint32	fat_size;
	uint32	data_start;
	uint32	root;
} FatFS;

typedef struct {
	uint32	size;					/* file size */
	uint32	cluster;				/* first cluster */
} FIL;

#ifndef _OSLIB_H_
typedef struct {
	uint32	cluster;
	uint32	sindex;
	uint32	offset;
	char	entry[16];
	uint32	entry_size;
	uint32	entry_isdir;
} DIR;
#endif

uint32 cluster2sector(FatFS *fat, uint32 cluster);
uint32 next_cluster(FatFS *fat, uint32 cluster);

int fat_mount(FatFS *fat, int partition);
uint32 fat_get_info(FatFS *fat, char *filename, uint32 *size, uint32 *isdir);

uint32 fat_next_dir(FatFS *fat, DIR *dir);

uint32 fat_read(FatFS *fat, uint32 cluster, uint32 offset, uint32 len, void* buffer);

#endif
