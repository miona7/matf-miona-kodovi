#define _XOPEN_SOURCE 700
#include <stdio.h>
#include <stdlib.h>

#include <sys/types.h>
#include <sys/stat.h>
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
#define BAF_MAX (1024)

int main(int argc, char** argv) {
    
    provera_greske(argc == 3, "");

    int dete_rod[MAX];
    provera_greske(pipe(dete_rod) != -1, "");

    pid_t dete_pid = fork();
    provera_greske(dete_pid != -1, "");

    if(dete_pid == 0) {

        struct stat fInfo;
        if(stat(argv[1], &fInfo) == 1) {
            exit(EXIT_FAILURE);
        }

        close(dete_rod[RD_END]);

        provera_greske(dup2(dete_rod[WR_END], STDOUT_FILENO) != -1, "");
        provera_greske(execlp("tail", "tail", "-n", argv[2], argv[1], NULL) != -1, "");

        close(dete_rod[WR_END]);
        exit(EXIT_SUCCESS);
    }

    close(dete_rod[WR_END]);

    int status = 0;
    provera_greske(wait(&status) != -1, "");

    if(WIFEXITED(status) && (WEXITSTATUS(status) == EXIT_SUCCESS)) {
        FILE* ulaz = fdopen(dete_rod[RD_END], "r");
        provera_greske(ulaz != NULL, "");
        
        char* linija = NULL;
        size_t n = 0;
        while(getline(&linija, &n, ulaz) != -1) {
            fprintf(stdout, "%s", linija);
        }
        fprintf(stdout, "\n");

        free(linija);
        fclose(ulaz);
    } else {
        fprintf(stdout, "Neuspeh\n");
    }

    close(dete_rod[RD_END]);
    exit(EXIT_SUCCESS);
}