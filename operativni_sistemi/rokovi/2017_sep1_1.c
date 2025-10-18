#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

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

#define MAX (64)

int sigusr1 = 0;
int sigusr2 = 0;
int sigterm = 0;

void rukovaoc_signalom(int sig) {
    switch(sig) {
        case SIGUSR1:
            sigusr1 = 1;
            break;
        case SIGUSR2:
            sigusr2 = 1;
            break;
        case SIGTERM:
            sigterm = 1;
            break;
    }
}

int main(int argc, char** argv) {
    
    char rec[MAX];
    while(1) {
        provera_greske(signal(SIGUSR1, rukovaoc_signalom) != SIG_ERR, "");
        provera_greske(signal(SIGUSR2, rukovaoc_signalom) != SIG_ERR, "");
        provera_greske(signal(SIGTERM, rukovaoc_signalom) != SIG_ERR, "");
        pause();
        
        if(sigterm) {
            break;
        }
        fscanf(stdin, "%s", rec);
        if(sigusr1) {
            int n = strlen(rec);
            for(int i = n-1; i >= 0; i--) {
                putchar(rec[i]);
            }
            putchar('\n');
            sigusr1 = 0;
        } else if(sigusr2) {
            int n = strlen(rec);
            char tmp[MAX]; int i = 0;
            for(i = 0; i < n; i++) {
                if(islower(rec[i])) {
                    tmp[i] = toupper(rec[i]);
                } else {
                    tmp[i] = rec[i]; 
                }
            }
            tmp[i] = '\0';
            fprintf(stdout, "%s\n", tmp);
            sigusr2 = 0;
        }
    } 

    exit(EXIT_SUCCESS);
}