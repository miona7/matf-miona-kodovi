#define _GNU_SOURCE 
#include <stdio.h>
#include <stdlib.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <signal.h>

#define provera_greske(uslov, poruka) \
    do { \
        if(!(uslov)) { \
            fprintf(stderr, "%s\n", poruka); \
            exit(EXIT_FAILURE); \
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
    
    provera_greske(argc == 1, "");

    int skor = 0;
    do {

        provera_greske(signal(SIGUSR1, rukovaoc_signalom) != SIG_ERR, "");
        provera_greske(signal(SIGUSR2, rukovaoc_signalom) != SIG_ERR, "");
        provera_greske(signal(SIGINT, rukovaoc_signalom) != SIG_ERR, "");
        provera_greske(signal(SIGTERM, rukovaoc_signalom) != SIG_ERR, "");
        pause();

        if(sigusr1) {
            skor += 1;
            sigusr1 = 0;
        }
        if(sigusr2) {
            skor += 2;
            sigusr2 = 0;
        }
        if(sigint) {
            skor -= 4;
            sigint = 0;
        }

    } while(sigterm);

    fprintf(stdout, "%d\n", skor);
    exit(EXIT_SUCCESS);
}