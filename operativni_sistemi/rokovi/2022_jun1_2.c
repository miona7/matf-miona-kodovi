#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
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
#define MAX_BAF (1024)

int main(int argc, char** argv) {

    int dete_rod[MAX];
    provera_greske(pipe(dete_rod) != -1, "");

    int dete_pid = fork();
    provera_greske(dete_pid != -1, "");

    if(dete_pid == 0) {
        close(dete_rod[RD_END]);

        provera_greske(dup2(dete_rod[WR_END], STDOUT_FILENO) != -1, "");
        provera_greske(execlp("pwd", "pwd", NULL) != -1, "");
    }
    
    close(dete_rod[WR_END]);

    int status = 0;
    provera_greske(wait(&status) != -1, "");

    if(WIFEXITED(status) && (WEXITSTATUS(status) == EXIT_SUCCESS)) {
        
        char bafer[MAX_BAF];
        int procitano = 0;
        provera_greske((procitano = read(dete_rod[RD_END], bafer, MAX_BAF)) != -1, "");
        
        char putanja[MAX_BAF];
        strncpy(putanja, bafer, 6);

        if(strcmp(putanja, "/home/") == 0) {
            char* ime = strtok(bafer + 6, "/");
            fprintf(stdout, "%s\n", ime);
        } else {
            fprintf(stdout, "system\n");
        }
    }
    
    close(dete_rod[RD_END]);
    
    exit(EXIT_SUCCESS);
}