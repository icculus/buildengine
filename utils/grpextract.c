/********************************************************************************
 *  BUILD group file extractor                                                  *
 *  Copyright (c) 2000 Christian Zander  [phoenix@minion.de]                    *
 *                                                                              *
 *  This program is free software; you can redistribute it and/or modify        *
 *  it under the terms of the GNU General Public License as published by        *
 *  the Free Software Foundation; either version 2 of the License, or           *
 *  (at your option) any later version.                                         *
 *                                                                              *
 *  This program is distributed in the hope that it will be useful,             *
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of              *
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the               *
 *  GNU General Public License for more details.                                *
 *                                                                              *
 *  You should have received a copy of the GNU General Public License           *
 *  along with this program; if not, write to the Free Software                 *
 *  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  *
 *                                                                              *
 ********************************************************************************/

#include <sys/types.h>
#include <sys/stat.h>
#include <ctype.h>
#include <fcntl.h>
#include <errno.h>
#include <fnmatch.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define PERMS	S_IWUSR|S_IWGRP|S_IRUSR|S_IRGRP|S_IROTH
#define CREAT	O_TRUNC|O_CREAT|O_WRONLY

typedef struct _grp_file_entry {
	char name[13];
	int  extract;
	long size;
	long offset;
} grp_file_entry;

int extract(int fdo, grp_file_entry *fp) {
	char buf[65536];
	long i, k;
	int fdd;
	
	if ((fdd = open(fp->name, CREAT, PERMS)) == -1) return -1;
	
	lseek(fdo, fp->offset, SEEK_SET);

	for (i = 0; i < fp->size; i += 65536) {
		if ((fp->size - i) < 65536) k = fp->size - i; else k = 65536;

		read(fdo, buf, k);
		if (write(fdd, buf, k) < k) return -1;
	}
	close(fdd);

	printf("Extracted %s\n", fp->name);
	
	return 0;
}

int main(int argc, char **argv) {
	grp_file_entry *fp;
	long filecount, offset;
	char buf[16];
	int fd, listonly, i, j;
	
	if (argc < 2) {
		printf("usage: %s [grouped file] [file ...]\n", argv[0]);
		printf("                                   \n"         );
		printf("  %s stuff.dat                     \n", argv[0]);
		printf("  %s stuff.dat *.map *.voc         \n", argv[0]);
		printf("  %s stuff.dat tiles000.art        \n", argv[0]);
		printf("                                   \n"         );
		exit(0);
	}
	
	if (argc == 2) listonly = 1; else listonly = 0;
	
	if ((fd = open(argv[1], O_RDONLY)) == -1) {
		printf("Error: opening %s, %s\n", argv[1], strerror(errno));
		exit(1);
	}
	
	read(fd, buf, 16);
	
	if (strncasecmp(buf, "KenSilverman", 12)) {
		close(fd);
		printf("Error: %s is not a valid group file\n", argv[1]);
		exit(1);
	}
	
	filecount = ((long)buf[12]	 & 0x000000ff) |
		    ((long)buf[13] << 8  & 0x0000ff00) |
		    ((long)buf[14] << 16 & 0x00ff0000) |
		    ((long)buf[15] << 24 & 0xff000000);

	offset = (filecount + 1) * 16;

	fp = malloc(sizeof(grp_file_entry) * filecount);
	memset(fp, 0, sizeof(grp_file_entry) * filecount);

	for (i = 0; i < filecount; i++) {
		read(fd, buf, 16);
		
		strncpy(fp[i].name, buf, 12);
		
		for (j = 0; j < 12; j++)
			fp[i].name[j] = (char)tolower(fp[i].name[j]);
		
		for (j = argc - 1; j > 1; j--) {
			if (fnmatch(argv[j], fp[i].name, FNM_NOESCAPE) == 0)
				fp[i].extract = 1;
		}
		
		fp[i].size = ((long)buf[12]	  & 0x000000ff) |
			     ((long)buf[13] << 8  & 0x0000ff00) |
			     ((long)buf[14] << 16 & 0x00ff0000) |
			     ((long)buf[15] << 24 & 0xff000000);
 
		fp[i].offset = offset;
		offset += fp[i].size;
	}	
	
	if (listonly) {
	
		printf("Filename         Size\n");
		printf("---------------------\n");
		
		for (i = 0; i < filecount; i++)
			printf("%-12s %8ld\n", fp[i].name, fp[i].size);
		
		free(fp); close(fd);
		exit(0);
	}
	
	for(i = 0; i < filecount; i++) {
		if (fp[i].extract) {
			if (extract(fd, &fp[i]) == -1)
				printf("Error: extracting %s, %s\n", fp[i].name, strerror(errno));
		}
	}
	
	free(fp); close(fd);
	return 0;
}
