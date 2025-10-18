#define _GNU_SOURCE 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
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
int sigquit = 0;

void rukovaoc_signalom(int signal) {
    switch(signal) {
        case SIGUSR1:
            sigusr1 = 1;
            break;
        case SIGUSR2:
            sigusr2 = 1;
            break;
        case SIGQUIT:
            sigquit = 1;
            break;
    }
}
 
int jeste_palindrom(char* rec) {
    int n = strlen(rec);
    for(int i = 0, j = n-1; i < j; i++, j--) {
        if(rec[i] != rec[j]) {
            return 0;
        }
    }
    return 1;
}

char* obrni(char* rec) {
    int n = strlen(rec);
    char* tmp = (char*)malloc((n+1)*sizeof(char));
    provera_greske(tmp != NULL, "");

    for(int i = 0, j = n-1; i < n; i++, j--) {
        tmp[i] = rec[j];
    }
    tmp[n] = '\0';
    
    return tmp;
}

int main(int argc, char** argv) {

    char* rec; 
    while(true) {

        fscanf(stdin, "%ms", &rec);

        provera_greske(signal(SIGUSR1, rukovaoc_signalom) != SIG_ERR, "");
        provera_greske(signal(SIGUSR2, rukovaoc_signalom) != SIG_ERR, "");
        provera_greske(signal(SIGQUIT, rukovaoc_signalom) != SIG_ERR, "");

        pause();

        if(sigquit) {
            break;
        }
        if(sigusr1) {
            sigusr1 = 0;
            fprintf(stdout, "%d\n", jeste_palindrom(rec));
        }
        if(sigusr2) {
            sigusr2 = 0;
            char* tmp = obrni(rec);
            fprintf(stdout, "%s\n", tmp);
            free(tmp);
        }
    }

    free(rec);
    exit(EXIT_SUCCESS);
}