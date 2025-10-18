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
#define MAX (2)
#define MAX_LINIJE (256)
#define BAF_MAX (4094)

int main(int argc, char** argv) {
    
    provera_greske(argc == 2, "");

    FILE* ulaz = fopen(argv[1], "r");
    provera_greske(ulaz != NULL, "");

    FILE* izlaz = fopen("errors.txt", "w");
    provera_greske(izlaz != NULL, "");

    char* linija = NULL;
    ssize_t velicina = 0;
    while(getline(&linija, &velicina, ulaz) > 0) {
        char komanda[MAX_LINIJE];
        char argument[MAX_LINIJE];
        sscanf(linija, "%s%s", komanda, argument);

        int dete_rod[MAX];
        provera_greske(pipe(dete_rod) != -1, "");

        pid_t dete_pid = fork();
        provera_greske(dete_pid != -1, "");

        if(dete_pid == 0) {
            close(dete_rod[RD_END]);

            provera_greske(dup2(dete_rod[WR_END], STDERR_FILENO) != -1, "");
            provera_greske(execlp(komanda, komanda, argument, NULL) != -1, "");
        }

        int status = 0;
        provera_greske(wait(&status) != -1, "");
        
        close(dete_rod[WR_END]);
        FILE* ulaz_za_greske = fdopen(dete_rod[RD_END], "r");
        provera_greske(ulaz_za_greske != NULL, "");
        
        int i = 0;
        char bafer_za_greske[BAF_MAX+1];
        while((bafer_za_greske[i] = getc(ulaz_za_greske)) != EOF) {
            i++;
        }
        bafer_za_greske[i] = '\0';

        fclose(ulaz_za_greske);

        if(WIFEXITED(status) && (WEXITSTATUS(status) != EXIT_SUCCESS)) {
           fprintf(izlaz, "%s", bafer_za_greske);
        }
        close(dete_rod[RD_END]);
    }

    fclose(ulaz);
    fclose(izlaz);
    free(linija);
    exit(EXIT_SUCCESS);
}