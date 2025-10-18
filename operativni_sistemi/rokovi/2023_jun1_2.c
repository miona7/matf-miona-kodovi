/*#define _XOPEN_SOURCE (700)
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

#define RD_END (0)
#define WR_END (1)
#define MAX (2)
#define MAX_BAF (256)

int main(int argc, char** argv) {
    
    provera_greske(argc == 1, "");

    char fajl[MAX_BAF];
    int broj_linija = 0;
    while(fscanf(stdin, "%s", fajl) == 1) {
        int dete_rod[MAX];
        //provera_greske(write(dete_rod[WR_END], fajl, strlen(fajl)) != -1, "");
        provera_greske(pipe(dete_rod) != -1, "");
        pid_t dete_pid = fork();
        provera_greske(dete_pid != -1, "");
        if(dete_pid == 0) {
            close(dete_rod[RD_END]);
            //char ime_fajla[MAX_BAF];
            //provera_greske(read(dete_rod[RD_END], ime_fajla, MAX_BAF) != -1, "");

            provera_greske(dup2(dete_rod[WR_END], STDOUT_FILENO) != -1, "");
            provera_greske(execlp("wc", "wc", "-l", fajl, NULL) != -1, "");   
        }

        int status = 0;
        provera_greske(wait(&status) != -1, "");
        close(dete_rod[WR_END]);

        if(WIFEXITED(status) && (WEXITSTATUS(status) == EXIT_SUCCESS)) {
            char bafer[MAX_BAF];
            provera_greske(read(dete_rod[RD_END], bafer, MAX_BAF) != -1, "");
            int br = 0;
            sscanf(bafer, "%d", &br);
            broj_linija += br;
        }
        close(dete_rod[RD_END]);
    }

    fprintf(stdout, "%d\n", broj_linija);
    exit(EXIT_SUCCESS);
}*/

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

#define RD_END (0)
#define WR_END (1)
#define MAX (2)
#define MAX_BAF (256)

int main(int argc, char** argv) {
    
    provera_greske(argc == 1, "");
    
    int broj_linija = 0;
    char fajl[MAX];
    while(fscanf(stdin, "%s", fajl) == 1) {
        int dete_rod[MAX];
        int rod_dete[MAX];
        provera_greske(pipe(dete_rod) != -1, "");
        provera_greske(pipe(rod_dete) != -1, "");

        pid_t dete_pid = fork();
        provera_greske(dete_pid != -1, "");

        if(dete_pid != 0) {
            close(dete_rod[WR_END]);
            close(rod_dete[RD_END]);

            provera_greske(write(rod_dete[WR_END], fajl, strlen(fajl)) != -1, "");

            char bafer[MAX_BAF];
            int procitano = read(dete_rod[RD_END], bafer, MAX_BAF - 1);
            provera_greske(procitano != -1, "");
            bafer[procitano] = '\0';

            int br = 0;
            sscanf(bafer, "%d", &br);
            broj_linija += br;

            close(dete_rod[RD_END]);
            close(rod_dete[WR_END]);
            provera_greske(wait(NULL) != -1, "");
        } else {
            close(dete_rod[RD_END]);
            close(rod_dete[WR_END]);

            char ime_fajla[MAX_BAF];
            int procitano = read(rod_dete[RD_END], ime_fajla, MAX_BAF - 1);
            provera_greske(procitano != -1, "");
            ime_fajla[procitano] = '\0';

            provera_greske(dup2(dete_rod[WR_END], STDOUT_FILENO) != -1, "");
            provera_greske(execlp("wc", "wc", "-l", ime_fajla, NULL) != -1, "");   

            close(dete_rod[WR_END]);
            close(rod_dete[RD_END]);
        }
    }
   
    fprintf(stdout, "%d\n", broj_linija);
    exit(EXIT_SUCCESS);
}