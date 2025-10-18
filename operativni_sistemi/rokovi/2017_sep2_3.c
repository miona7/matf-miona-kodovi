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

int main(int argc, char** argv) {

    char* linija = NULL;
    size_t velicina = 0;

    while(getline(&linija, &velicina, stdin) != -1) {
        int dete_rod[MAX];
        provera_greske(pipe(dete_rod) != -1, "");

        pid_t dete_pid = fork();
        provera_greske(dete_pid != -1, "");

        if(dete_pid == 0) {
            close(dete_rod[RD_END]);

            //char op1[MAX], op2[MAX];
            char* op1 = (char*)malloc(MAX*sizeof(char));
            provera_greske(op1 != NULL, "");
            char* op2 = (char*)malloc(MAX*sizeof(char));
            provera_greske(op2 != NULL, "");
            char* op = (char*)malloc(MAX*sizeof(char));
            provera_greske(op != NULL, "");
            sscanf(linija, "%s %s %s", op1, op2, op);
            /*if(strcmp(op, "*") == 0) {
                op = "*";
            }*/
            //fprintf(stdout, "%s %s %s\n", op1, op, op2);

            provera_greske(dup2(dete_rod[WR_END], STDOUT_FILENO) != -1, "");
            provera_greske(execlp("expr", "expr", op1, op, op2, NULL) != -1, "");

            close(dete_rod[WR_END]);
            exit(EXIT_SUCCESS);
        }
        close(dete_rod[WR_END]);
        FILE* ulaz = fdopen(dete_rod[RD_END], "r");
        provera_greske(ulaz != NULL, "");
        int rez;
        fscanf(ulaz, "%d", &rez);
        fclose(ulaz);
        fprintf(stdout, "%d\n", rez);
        close(dete_rod[RD_END]);
        provera_greske(wait(NULL) != -1, "");
    }

    free(linija);
    exit(EXIT_SUCCESS);
}