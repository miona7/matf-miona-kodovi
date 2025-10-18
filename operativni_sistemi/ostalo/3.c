#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#define MAX (11)

#define provera_greske(uslov, poruka) \
    do { \
        if(!(uslov)) { \
            fprintf(stderr, "%s\n", poruka); \
            exit(EXIT_FAILURE); \
        } \
    } while(0)

void ispis(const char* fpath, char** s) {

    struct stat fInfo;
    provera_greske(stat(fpath, &fInfo) != -1, "stat");
    
    *s = (char*)malloc(MAX*sizeof(char));
    provera_greske(s != NULL, "malloc");

    char prava_pristupa[MAX] = "-rwxrwxrwx";

    switch(fInfo.st_mode & __S_IFMT) {
        case __S_IFDIR:
            prava_pristupa[0] = 'd';
            break;
        case __S_IFREG:
            prava_pristupa[0] = '-';
            break;
        default:
            exit(EXIT_FAILURE);
    }

    if(!(fInfo.st_mode & S_IRUSR)) {
        prava_pristupa[1] = '-';
    }
    if(!(fInfo.st_mode & S_IWUSR)) {
        prava_pristupa[2] = '-';
    }
    if(!(fInfo.st_mode & S_IXUSR)) {
        prava_pristupa[3] = '-';
    }

    if(!(fInfo.st_mode & S_IRGRP)) {
        prava_pristupa[4] = '-';
    }
    if(!(fInfo.st_mode & S_IWGRP)) {
        prava_pristupa[5] = '-';
    }
    if(!(fInfo.st_mode & S_IXGRP)) {
        prava_pristupa[6] = '-';
    }

    if(!(fInfo.st_mode & S_IROTH)) {
        prava_pristupa[7] = '-';
    }
    if(!(fInfo.st_mode & S_IWOTH)) {
        prava_pristupa[8] = '-';
    }
    if(!(fInfo.st_mode & S_IXOTH)) {
        prava_pristupa[9] = '-';
    }

    sprintf(*s, "%s", prava_pristupa);
}

int main(int argc, char** argv) {

    provera_greske(argc == 2, "");

    char* s = NULL;

    ispis(argv[1], &s);
    fprintf(stdout, "%s\n", s);

    free(s);
    exit(EXIT_SUCCESS);
}