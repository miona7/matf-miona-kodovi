#define _XOPEN_SOURCE (700)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
#define MAX_PP (2)
#define MAX (256)

int main(int argc, char** argv) {
    
    provera_greske(argc == 2, "");

    FILE* ulaz = fopen(argv[1], "r");
    provera_greske(ulaz != NULL, "");

    char max_komanda[MAX];
    char max_argument[MAX];
    int max = -1;

    char* linija = NULL;
    ssize_t n = 0;
    while(getline(&linija, &n, ulaz) > 0) {
        char komanda[MAX];
        char argument[MAX];
        sscanf(linija, "%s%s", komanda, argument);

        int dete_rod[MAX_PP];
        provera_greske(pipe(dete_rod) != -1, "");

        pid_t dete_pid = fork();
        provera_greske(dete_pid != -1, "");

        if(dete_pid == 0) {
            close(dete_rod[RD_END]);

            provera_greske(dup2(dete_rod[WR_END], STDOUT_FILENO) != -1, "");
            provera_greske(execlp(komanda, komanda, argument, NULL) != -1, "");
        }

        close(dete_rod[WR_END]);
        
        int status = 0;
        provera_greske(wait(&status) != -1, "");

        if(WIFEXITED(status) && (WEXITSTATUS(status) == EXIT_SUCCESS)) {
            
            char bafer[MAX];
            int procitano = 0;
            int br = 0;
            while((procitano = read(dete_rod[RD_END], bafer, MAX)) > 0) {
                br += procitano;
            }
            provera_greske(procitano != -1, "");

            if(br > max) {
                max = br;
                strcpy(max_komanda, komanda);
                strcpy(max_argument, argument);
            }
        }

        close(dete_rod[RD_END]);
    }

    fprintf(stdout, "%s %s\n", max_komanda, max_argument);

    free(linija);
    fclose(ulaz);
    exit(EXIT_SUCCESS);
}