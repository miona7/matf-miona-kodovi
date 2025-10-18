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
#define MAX_LINIJE (255)
#define MAX_BAF (1024)

int main(int argc, char** argv) {
    
    int br_neuspesnih = 0;
    char komanda_max[MAX+1];
    int max_karaktera = -1;

    char* linija = NULL;
    size_t n = 0;

    while(getline(&linija, &n, stdin) > 0) {
        int n;
        int ukupno_procitano = 0;
        int procitano = 0;
        sscanf(linija + ukupno_procitano, "%d%*c%n", &n, &procitano);
        ukupno_procitano += procitano;

        char** komande = (char**)malloc((n+1)*sizeof(char*));
        provera_greske(komande != NULL, "");
        for(int i = 0; i < n; i++) {
            komande[i] = (char*)malloc((MAX_LINIJE + 1)*sizeof(char));
            provera_greske(komande[i] != NULL, "");
        }

        for(int i = 0; i < n; i++) {
            sscanf(linija + ukupno_procitano, "%s%*c%n", komande[i], &procitano);
            ukupno_procitano += procitano;
        }
        komande[n] = NULL;

        int dete_rod[MAX];
        provera_greske(pipe(dete_rod) != -1, "");

        pid_t dete_pid = fork();

        if(dete_pid == 0) {
            close(dete_rod[RD_END]);

            provera_greske(dup2(dete_rod[WR_END], STDOUT_FILENO) != -1, "");
            provera_greske(execvp(komande[0], komande) != -1, "");
        }

        int status = 0;
        provera_greske(wait(&status) != -1, "");
        close(dete_rod[WR_END]);

        if(WIFEXITED(status) && (WEXITSTATUS(status) == EXIT_SUCCESS)) {
            int uk_pr = 0;
            int pr = 0;
            char bafer[MAX_BAF];
            while((pr = read(dete_rod[RD_END], bafer, MAX_BAF)) > 0) {
                uk_pr += pr;
            }            
            provera_greske(pr != -1, "");
            if(uk_pr > max_karaktera) {
                max_karaktera = uk_pr;
                strcpy(komanda_max, komande[0]);
            }

        } else {
            br_neuspesnih++;
        }

        close(dete_rod[RD_END]);
        for(int i = 0; i < n; i++) {
            free(komande[i]);
        }
        free(komande);
    }

    char* nema = "nema";
    fprintf(stdout, "%d %s\n", br_neuspesnih, (max_karaktera != -1 ? komanda_max : nema));

    free(linija);
    exit(EXIT_SUCCESS);
}