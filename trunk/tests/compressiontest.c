#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "engine_protos.h"

void setvmode(int x) { }

#define CACHESIZE ((1024 * 1024) * 4)

int main(int argc, char **argv)
{
    FILE *f = fopen("buildinf.txt", "rb");
    long len = filelength(fileno(f));
    char *inbuf = (char *) malloc(len);
    char *cmpbuf = (char *) malloc(len);
    char *cachebuf = (char *) malloc(CACHESIZE);
    fread(inbuf, len, 1, f);
    fclose(f);

    initcache((long) cachebuf, CACHESIZE);

    f = fopen("buildinf.txt.kz", "wb");
    dfwrite(inbuf, len, 1, f);
    fclose(f);

    memset(cmpbuf, '\0', len);
    f = fopen("buildinf.txt.kz", "rb");
    dfread(cmpbuf, len, 1, f);
    fclose(f);
    remove("buildinf.txt.kz");

    printf("%s\n", (memcmp(inbuf, cmpbuf, len) == 0) ? "passed" : "failed");

    free(inbuf);
    free(cmpbuf);
    return(0);
}

