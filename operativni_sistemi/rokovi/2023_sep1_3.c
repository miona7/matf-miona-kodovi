#define _XOPEN_SOURCE (700)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <unistd.h>

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
#define MAX_BAF (256)

int main(int argc, char** argv) {
    
    int dete_rod[MAX];
    provera_greske(pipe(dete_rod) != -1, "");

    pid_t dete_pid = fork();
    provera_greske(dete_pid != -1, "");

    if(dete_pid == 0) {
        close(dete_rod[RD_END]);
        provera_greske(dup2(dete_rod[WR_END], STDOUT_FILENO) != -1, "");
        provera_greske(execlp("pwd", "pwd", NULL) != -1, "");
    }

    int status = 0;
    provera_greske(wait(&status) != -1, "");
    close(dete_rod[WR_END]);

    if(WIFEXITED(status) && (WEXITSTATUS(status) == EXIT_SUCCESS)) {
        char bafer[MAX_BAF + 1];
        int procitano = read(dete_rod[RD_END], bafer, MAX_BAF);
        provera_greske(procitano != -1, "");
        bafer[procitano-1] = '\0';
        fprintf(stdout, "%ld\n", strlen(bafer));
    }
    close(dete_rod[RD_END]);
    exit(EXIT_SUCCESS);
}