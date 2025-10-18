#define _XOPEN_SOURCE 700
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
#define BAF_MAX (1024)

int main(int argc, char** argv) {
    
    provera_greske(argc > 1, "");

    char** komanda = (char**)malloc((argc+1)*sizeof(char*));
    provera_greske(komanda != NULL, "");
    komanda[0] = (char*)malloc((strlen(argv[1])+1)*sizeof(char));
    provera_greske(komanda[0] != NULL, "");
    strcpy(komanda[0], argv[1]);
    for(int i = 1; i < argc; i++) {
        komanda[i] = (char*)malloc((strlen(argv[i])+1)*sizeof(char));
        provera_greske(komanda[i] != NULL, "");
        strcpy(komanda[i], argv[i]);
    }
    komanda[argc] = NULL;

    int dete_rod[MAX];
    provera_greske(pipe(dete_rod) != -1, "");

    pid_t dete_pid = fork();
    provera_greske(dete_pid != -1, "");

    if(dete_pid == 0) {
        close(dete_rod[RD_END]);
        provera_greske(dup2(dete_rod[WR_END], STDOUT_FILENO) != -1, "");
        provera_greske(execvp(komanda[0], komanda+1) != -1, "");

        close(dete_rod[WR_END]);
        exit(EXIT_SUCCESS);
    }
    close(dete_rod[WR_END]);
    int status = 0;
    provera_greske(wait(&status) != -1, "");

    if(WIFEXITED(status) && (WEXITSTATUS(status) == EXIT_SUCCESS)) {
        FILE* ulaz = fdopen(dete_rod[RD_END], "r");
        provera_greske(ulaz != NULL, "");
        
        int brojac = 0;
        char* linija = NULL;
        size_t n = 0;
        while(getline(&linija, &n, ulaz) != -1) {
            brojac++;
        }
        free(linija);
        fclose(ulaz);
        fprintf(stdout, "%d\n", brojac);
    } else {
        fprintf(stdout, "Neuspeh\n");
        provera_greske(0, "");
    }

    for(int i = 0; i < argc; i++) {
        free(komanda[i]);
    }
    free(komanda);
    close(dete_rod[RD_END]);
    exit(EXIT_SUCCESS);
}