#include <stdio.h>
#include <stdlib.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#define provera_greske(uslov, poruka) \
    do { \
        if(!(uslov)) { \
            fprintf(stderr, "%s\n", poruka); \
            exit(EXIT_FAILURE); \
        } \
    } while(0)

int main(int argc, char** argv) {

    provera_greske(argc == 2, "");

    mode_t pravaPristupa = 0777;
    provera_greske(mkdir(argv[1], pravaPristupa) != -1, "");

    provera_greske(chmod(argv[1], pravaPristupa) != -1, "");

    exit(EXIT_SUCCESS);
}