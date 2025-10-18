#include <stdio.h>
#include <stdlib.h>

#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>

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

char* ekstenzija(const char* ime) {
    char* ext = strrchr(ime, '.');
    provera_greske(ext != NULL, "");
    int n = strlen(ext);
    ext[n-1] = '\0';
    return ext;
}

int main(int argc, char** argv) {

    provera_greske(argc == 2, "");
    int dete_rod[MAX];
    provera_greske(pipe(dete_rod) != -1, "");

    pid_t dete_pid = fork();
    provera_greske(dete_pid != -1, "");

    if(dete_pid == 0) {
        close(dete_rod[RD_END]);

        provera_greske(dup2(dete_rod[WR_END], STDOUT_FILENO) != -1, "");
        provera_greske(execlp("find", "find", ".", "-type", "f", NULL) != -1, "");

        close(dete_rod[WR_END]);
        exit(EXIT_SUCCESS);
    }

    close(dete_rod[WR_END]);
    provera_greske(wait(NULL) != -1, "");

    FILE* ulaz = fdopen(dete_rod[RD_END], "r");
    provera_greske(ulaz != NULL, "");

    char* linija = NULL;
    size_t n = 0;
    int brojac = 0;

    while(getline(&linija, &n, ulaz) != -1) {
        char* ext = ekstenzija(linija);
        if(strcmp(argv[1], ext) == 0) {
            brojac++;
        }
    }
    fprintf(stdout, "%d\n", brojac);
    
    close(dete_rod[RD_END]);
    fclose(ulaz);
    free(linija);
    exit(EXIT_SUCCESS);
}