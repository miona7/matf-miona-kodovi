#define _XOPEN_SOURCE (700)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>

#define provera_greske(uslov, poruka) \
    do { \
        if(!(uslov)) { \
            fprintf(stderr, "%s\n", poruka); \
            exit(EXIT_FAILURE); \
        } \
    } while(0)

#define RD_END (0)
#define WR_END (1)
#define MAX (2)
#define BAF_MAX (512)

int main(int argc, char** argv) {
    
    provera_greske(argc > 1, "");

    for(int i = 1; i < argc; i++) {
        
        int dete_rod[MAX];
        provera_greske(pipe(dete_rod) != -1, "");

        pid_t dete_pid = fork();
        provera_greske(dete_pid != -1, "");

        if(dete_pid == 0) {
            close(dete_rod[RD_END]);
            provera_greske(dup2(dete_rod[WR_END], STDOUT_FILENO) != -1, "");
            provera_greske(execlp("du", "du", "-sch", argv[i], NULL) != -1, "");
        }

        close(dete_rod[WR_END]);
        int status = 0;
        provera_greske(wait(&status) != -1, "");

        char bafer[BAF_MAX];
        int procitano = read(dete_rod[RD_END], bafer, BAF_MAX-1);
        provera_greske(procitano != -1, "");
        bafer[procitano] = '\0';

        if(WIFEXITED(status) && (WEXITSTATUS(status) == EXIT_SUCCESS)) {
            
            char rez[BAF_MAX];
            sscanf(bafer, "%s", rez);
            fprintf(stdout, "%s ", rez);
            
        } else {
            fprintf(stdout, "neuspeh ");
        }

        close(dete_rod[RD_END]);
    }

    fprintf(stdout, "\n");
    exit(EXIT_SUCCESS);
}