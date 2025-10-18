#define _XOPEN_SOURCE (700)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#define KB (1024)
#define MB (1024*1024)
#define GB (1024*1024*1024)

#define provera_greske(uslov, poruka) \
    do { \
        if(!(uslov)) { \
            fprintf(stderr, "%s\n", poruka); \
            exit(EXIT_FAILURE); \
        } \
    } while(0)

int main(int argc, char** argv) {

    provera_greske(argc == 3, "");

    struct stat fInfo;
    provera_greske(stat(argv[1], &fInfo) != -1, "");
    // provera_greske(S_ISREG(fInfo.st_mode), "");

    double velicina = 0;
    char* s = NULL;

    if(strcmp(argv[2], "KB") == 0) {
        velicina = (double) (fInfo.st_size * 1.0 / KB);
        // fprintf(stdout, "%s %dKB\n", argv[1], (int)ceil((double)fInfo.st_size/KB)); 
        s = "KB";       
    }
    else if(strcmp(argv[2], "MB") == 0) {
        velicina = (double) (fInfo.st_size * 1.0 / MB);
        // fprintf(stdout, "%s %dMB\n", argv[1], (int)ceil((double)fInfo.st_size/MB));    
        s = "MB";    
    }
    else if(strcmp(argv[2], "GB") == 0) {
        velicina = (double) (fInfo.st_size * 1.0 / GB);
        // fprintf(stdout, "%s %dGB\n", argv[1], (int)ceil((double)fInfo.st_size/GB)); 
        s = "GB";       
    } else {
        provera_greske(0, "");
    }

    velicina = ceil(velicina);
    char* ime = strrchr(argv[1], '/');

    fprintf(stdout, "%s %d%s\n", ime == NULL ? argv[1] : ime+1, (int)velicina, s);

    exit(EXIT_SUCCESS);
}