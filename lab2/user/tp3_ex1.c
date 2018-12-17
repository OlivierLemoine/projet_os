#include <stdlib.h>
#include <stdio.h>
#include <oslib.h>
#include <string.h>
#include <termio.h>
#include <diskio.h>
#include "lexer.h"
#include <fat.h>

#define MIN(a,b) ((a)<(b)? (a) : (b))
#define MAX(a,b) ((a)>(b)? (a) : (b))

int cpt=0;
Semaphore * mutex;

uint8  buf[512];
char text[80];

void tache1()
{
	FatFS fs;
	uint8 res=0, b;
	int32 p2, sector=0;
	int k, ofs;
	
	term_init(80,24);
	term_clrscr();
	
	while(1) {
		readline(">", text, 60);
		lexer_reset(text);
		next_token();
		switch(token) {
		case T_DISK_INIT:	/* di - Initialize disk */
			term_printf("\nDisk Initialize : rc=%d\n", (int32)disk_initialize());
			break;
		case T_DISK_STATUS:	/* ds - Show disk status */
			if (disk_ioctl(GET_SECTOR_COUNT, &p2) == RES_OK) {
				term_printf("\nDrive size : %u sectors\n", p2);
			}
			if (disk_ioctl(GET_BLOCK_SIZE, &p2) == RES_OK) {
				term_printf("Block size : %u sectors\n", p2);
			}
			if (disk_ioctl(MMC_GET_TYPE, &b) == RES_OK) {
				term_printf("Media type : %u ", b);
				if (b==1) term_printf("(MMC)\n");
				else if (b==2) term_printf("(SDCARD v1)\n");
				else if (b==4) term_printf("(SDCARD v2)\n");
				else term_printf("(Unknown)\n");
			}
			if (disk_ioctl(MMC_GET_CSD, buf) == RES_OK) {
				term_printf("CSD        : "); 
				for (k=0;k<16;k++) term_printf("%02x", buf[k]);
				term_printf("\n");
			}
			if (disk_ioctl(MMC_GET_CID, buf) == RES_OK) {
				term_printf("CID        : ");
				for (k=0;k<16;k++) term_printf("%02x", buf[k]);
				term_printf("\n");
			}
			if (disk_ioctl(MMC_GET_OCR, buf) == RES_OK) {
				term_printf("OCR        : ");
				for (k=0;k<4;k++) term_printf("%02x", buf[k]);
				term_printf("\n");
			}
			break;
		case T_DISK_DUMP:	/* dd [<lba>] - Dump sector */
			next_token();
			if (token==T_NUM) sector=token_val;
			res = disk_read(buf, sector, 1);
			if (res) { term_printf("\nrc=%d\n", (uint32)res); break; }
			term_printf("\nDumping sector %u ...\n", sector);
			for (ofs = 0; ofs < 512; ofs+=16) {
				term_printf("0x%03x : ", ofs);
				for (k=0;k<16;k++) term_printf("%02x ", buf[ofs+k]);
				term_printf("  ");
				for (k=0;k<16;k++) {
					char c=buf[ofs+k];
					if (c<0x20 || c>0x7F) c='.';
					term_printf("%c", c);
				}
				term_printf("\n");
			}
			for (k=0;k<80;k++) term_printf("-");
			term_printf("\n");
			sector ++;
			break;
		case T_MOUNT:
			fat_mount(&fs, 0);
			term_printf("\ncluster size      = %u\n", fs.csize);
			term_printf("part start sector = %u\n", fs.part_start);
			term_printf("fat size          = %u\n", fs.fat_size);
			term_printf("data start sector = %u\n", fs.data_start);
			break;
		case T_STAT:
			next_token();
			if (token==T_TEXT) {
				uint32 cluster, isdir, size;
				cluster=fat_get_info(&fs, token_str, &size, &isdir);
				if (cluster) {
					term_printf("\n'%s' is a %s\n", token_str, isdir ? "directory" : "file");
					term_printf("  size          : %u\n", size);
					term_printf("  start cluster : %u\n", cluster);
					term_printf("  start sector  : %u\n", cluster2sector(&fs, cluster));
					uint32 i=0;
					do {
						uint32 sector = cluster2sector(&fs, cluster);
						term_printf("  block %u --> cluster 0x%x (sector %u - %u)\n", i++, cluster, sector, sector+fs.csize-1);
						cluster=next_cluster(&fs, cluster);
					} while (cluster < 0xffffff8);
				} else {
					term_printf("\nNo such file or directory\n");
				}
			}
			break;
		case T_LS: {
				DIR dir;
				uint32 cluster, isdir, size;
				next_token();
				if (token==T_TEXT) {
					cluster = fat_get_info(&fs, token_str, &size, &isdir);
				} else {
					cluster = fat_get_info(&fs, "/", &size, &isdir);
				}
				if (cluster && isdir) {
					dir.cluster = cluster;
					dir.sindex  = 0;
					dir.offset  = 0;

					term_printf("\n");
					while (fat_next_dir(&fs, &dir)) {
						term_printf("  [%s] [%8d] %s\n", dir.entry_isdir ? "dir " : "file", dir.entry_size, dir.entry);
					}
				} else {
					term_printf("\n%s is not a directory\n", token_str);
				}
			}
			break;
		case T_CAT:
			next_token();
			if (token==T_TEXT) {
				uint32 cluster, isdir, size;
				cluster=fat_get_info(&fs, token_str, &size, &isdir);
				
				if (cluster && !isdir) {
					term_putc('\n');

					uint32 offset=0;
					int n=fat_read(&fs, cluster, offset, MIN(size, 512), (char*)buf);
					
					while (n) {
						int i;
						for (i=0;i<n;i++) term_putc(buf[i]);
						offset+=n;
						size-=n;
						n=fat_read(&fs, cluster, offset, MIN(size, 512), (char*)buf);
					}
					
					term_putc('\n');
				} else if (cluster)
					term_printf("\n%s is not a file\n", token_str);
				else
					term_printf("\n%s : no such file\n", token_str);
			}
			break;
		case T_HELP:
			term_printf(
				"\n[Disk controls]\n"
				" di             - initialize disk\n"
				" dd [<sect>]    - dump a sector\n"
				" ds             - show disk status\n"
				" mount          - mount SD card\n"
				" ls [dirpath]   - list directory content\n"
				" cat filepath   - ouput file content\n"
				" stat filepath  - get info on file cluster list\n"
				"\n"
			);
			break;
		default:
			term_printf("\nUnknown command\n");
			break;
		}
	}
}

void idle()
{
    while(1) {}
}


int main()
{
    mutex=sem_new(1);

    task_new(tache1,1024);
    task_new(idle,4);

    os_start();

    return 0;
}
