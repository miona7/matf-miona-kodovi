#define _XOPEN_SOURCE (700)
#define _GNU_SOURCE 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <sys/mman.h>
#include <unistd.h>
#include <fcntl.h>
#include <dirent.h>
#include <errno.h>
#include <pthread.h>
#include <signal.h>
#include <semaphore.h>

#define provera_greske(uslov, poruka) \
    do { \
        if(!(uslov)) { \
            fprintf(stderr, "%s\n", poruka); \
            exit(EXIT_FAILURE); \
        } \
    } while(0)

#define provera_greske_niti(gr, poruka) \
    do { \
        int greska = gr; \
        if(greska) { \
            errno = greska; \
            provera_greske(0, poruka); \
        } \
    } while(0)

#define MAX (1024)

int sigusr1 = 0;
int sigusr2 = 0;
int sigquit = 0;

void rukovaoc_signalom(int signal) {
    switch(signal) {
        case SIGUSR1:
            sigusr1 = 1;
            break;
        case SIGUSR2:
            sigusr2 = 2;
            break;
        case SIGQUIT:  
            sigquit = 1;
            break;
    }
}

int main(int argc, char** argv) {
    
    char fajl[MAX];

    while(1) {

        provera_greske(signal(SIGUSR1, rukovaoc_signalom) != SIG_ERR, "");
        provera_greske(signal(SIGUSR2, rukovaoc_signalom) != SIG_ERR, "");
        provera_greske(signal(SIGQUIT, rukovaoc_signalom) != SIG_ERR, "");
        pause();


        if(sigquit) {
            break;
        }

        fscanf(stdin, "%s", fajl);


        if(sigusr1) {
            sigusr1 = 0;
            struct stat fInfo;
            provera_greske(stat(fajl, &fInfo) != -1, "");
            fprintf(stdout, "%ld\n", fInfo.st_size);
        }
        if(sigusr2) {
            sigusr2 = 0;
            struct stat fInfo;
            provera_greske(stat(fajl, &fInfo) != -1, "");
            struct tm* vreme = localtime(&fInfo.st_mtime);
            provera_greske(vreme != NULL, "");
            fprintf(stdout, "%d\n", vreme->tm_mday);
        }

    }

    exit(EXIT_SUCCESS);
}
