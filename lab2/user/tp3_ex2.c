#include <stdlib.h>
//#include <stdio.h>
#include <oslib.h>
#include <string.h>
#include <termio.h>
#include <diskio.h>
#include "lexer.h"
#include <fat.h>

uint8  buf[512];
char text[80];

void tache1()
{
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
			mount();
			break;
		case T_LS: {
				int fd;
				next_token();
				if (token==T_TEXT) fd=open(token_str, O_READ);
				else fd=open("/", O_READ);
				if (fd!=-1) {
					DIR *dir;
					term_printf("\n");
					while (readdir(fd, &dir)==0) {
						term_printf("  [%s] [%8d] %s\n", dir->entry_isdir ? "dir " : "file", dir->entry_size, dir->entry);
					}
					close(fd);
				} else {
					term_printf("\n%s is not a directory\n", token_str);
				}
			}			break;
		case T_CAT:
			next_token();
			if (token==T_TEXT) {
				term_putc('\n');
				int fd = open(token_str, O_READ);
				if (fd!=-1) {
					int n=read(fd, buf, 512);
					while (n > 0) {
						int i;
						for (i=0;i<n;i++) term_putc(buf[i]);
						n=read(fd, buf, 512);
					}
					close(fd);
					term_putc('\n');
				} else term_printf("%s : no such file\n", token_str);
			}
			break;
		case T_ECHO:
			next_token();
			if (token==T_NUM) {
				uint8 val=token_val;
				next_token();
				if (token==T_TEXT) {
					int fd=open(token_str, O_WRITE);
					if (fd!=-1) {
						write(fd, &val,1);
						close(fd);
						term_putc('\n');
					}
				} else term_printf("\necho : file path expexted\n");
			} else term_printf("\necho : numerical value expexted\n");
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
    task_new(tache1,1024);
    task_new(idle,128);

    os_start();

    return 0;
}
