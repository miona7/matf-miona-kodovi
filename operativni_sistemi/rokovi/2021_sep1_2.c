#define _GNU_SOURCE
#define _XOPEN_SOURCE (700)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <sys/mman.h>
#include <unistd.h>
#include <fcntl.h>
#include <dirent.h>
#include <errno.h>
#include <pthread.h>
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

int sigusr1 = 0;
int sigusr2 = 0;
int sigint = 0;
int sigterm = 1;

void rukovaoc_signalom(int signal) {
    switch(signal) {
        case SIGUSR1: 
            sigusr1 = 1;
            break;
        case SIGUSR2:
            sigusr2 = 1;
            break;
        case SIGINT:
            sigint = 1;
            break;
        case SIGTERM:
            sigterm = 0;
            break;
    }
}

int main(int argc, char** argv) {
    
    int brojac = 0;

    do {
        provera_greske(signal(SIGUSR1, rukovaoc_signalom) != SIG_ERR, "");
        provera_greske(signal(SIGUSR2, rukovaoc_signalom) != SIG_ERR, "");
        provera_greske(signal(SIGINT, rukovaoc_signalom) != SIG_ERR, "");
        provera_greske(signal(SIGTERM, rukovaoc_signalom) != SIG_ERR, "");

        pause();

        if(sigusr1) {
            sigusr1 = 0;
            brojac += 1;
        }
        if(sigusr2) {
            sigusr2 = 0;
            brojac += 2;
        }
        if(sigint) {
            sigint = 0;
            brojac -= 4;
        }
    } while(sigterm);
    
    fprintf(stdout, "%d\n", brojac);
    exit(EXIT_SUCCESS);
}
