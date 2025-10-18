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

#define RD_END (0)
#define WR_END (1)
#define MAX (2)

int main(int argc, char** argv) {
    
    provera_greske(argc == 2, "");

    struct stat f_info;
    provera_greske(stat(argv[1], &f_info) != -1, "");
    provera_greske(S_ISREG(f_info.st_mode), "");

    char* s = strrchr(argv[1], '.');
    if(s != NULL && (strcmp(s, ".c") != 0)) {
        provera_greske(0, "");
    }

    int n = strlen(argv[1]);
    char* novi_fajl = (char*)malloc(n*sizeof(char));
    provera_greske(novi_fajl != NULL, "");

    strcpy(novi_fajl, argv[1]);
    novi_fajl[n-1] = 's';

    int dete_rod[MAX];
    provera_greske(pipe(dete_rod) != -1, "");

    pid_t dete_pid = fork();
    provera_greske(dete_pid != -1, "");

    if(dete_pid == 0) {
        close(dete_rod[RD_END]);

        provera_greske(dup2(dete_rod[WR_END], STDOUT_FILENO) != -1, "");
        provera_greske(execlp("gcc", "gcc", "-std=c99", argv[1], "-o", novi_fajl, NULL) != -1, "");
    }

    close(dete_rod[WR_END]);

    int status = 0;
    provera_greske(wait(&status) != -1, "");

    if(WIFEXITED(status)) { 
        if(WEXITSTATUS(status) == EXIT_SUCCESS) {
            FILE* ulaz = fopen(novi_fajl, "r");
            provera_greske(ulaz != NULL, "");

            char* linija = NULL;
            size_t n = 0;
            int brojac = 0;
            while(getline(&linija, &n, ulaz) > 0) {
                if(strstr(linija, "mov") != NULL) {
                    brojac++;
                }
            }
            fprintf(stdout, "%d\n", brojac);
            free(linija);
        } else {
            free(novi_fajl);
            exit(WEXITSTATUS(status));
        }
    } else {
        free(novi_fajl);
        provera_greske(0, "");
    }

    close(dete_rod[RD_END]);

    provera_greske(unlink(novi_fajl) != -1, "");
    free(novi_fajl);
    exit(EXIT_SUCCESS);
}
