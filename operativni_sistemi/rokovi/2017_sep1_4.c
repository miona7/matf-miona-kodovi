#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#define MAX (4)

#define provera_greske(uslov, poruka) \
    do { \
        if(!(uslov)) { \
            fprintf(stderr, "%s\n", poruka); \
            exit(EXIT_FAILURE); \
        } \
    } while(0)

int main(int argc, char** argv) {

    provera_greske(argc == 2, "");
    time_t t = atoi(argv[1]);
    char* s = ctime(&t);
    char m[MAX];
    provera_greske(sscanf(s, "%s", m) != EOF, "");
    if(strcmp(m, "Mon") == 0) {
        fprintf(stdout, "ponedeljak");
    } else if(strcmp(m, "Tue") == 0) {
        fprintf(stdout, "utorak");
    } else if(strcmp(m, "Wed") == 0) {
        fprintf(stdout, "sreda");
    } else if(strcmp(m, "Thu") == 0) {
        fprintf(stdout, "cetvrtak");
    } else if(strcmp(m, "Fri") == 0) {
        fprintf(stdout, "petak");
    } else if(strcmp(m, "Sat") == 0) {
        fprintf(stdout, "subota");
    } else {
        fprintf(stdout, "nedelja");
    }

    exit(EXIT_SUCCESS);
}