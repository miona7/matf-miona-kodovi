#include <stdio.h>
#include <stdlib.h>
#include <time.h>

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
    
    provera_greske(argc == 3, "");

    time_t sekunde = atol(argv[1]);
    struct tm* vreme = localtime(&sekunde);
    provera_greske(vreme != NULL, "");

    switch (vreme->tm_wday) {
        case 0:
            fprintf(stdout, "nedelja ");
            break;
        case 1:
            fprintf(stdout, "ponedeljak ");
            break;
        case 2:
            fprintf(stdout, "utorak ");
            break;
        case 3:
            fprintf(stdout, "sreda ");
            break;
        case 4:
            fprintf(stdout, "cetvrtak ");
            break;
        case 5:
            fprintf(stdout, "petak ");
            break;
        case 6:
            fprintf(stdout, "subota ");
            break;
    }

    vreme->tm_year += atoi(argv[2]);
    sekunde = mktime(vreme);
    provera_greske(sekunde != (time_t)-1, "");
    vreme = localtime(&sekunde);
    provera_greske(vreme != NULL, "");

    switch (vreme->tm_wday) {
        case 0:
            fprintf(stdout, "nedelja\n");
            break;
        case 1:
            fprintf(stdout, "ponedeljak\n");
            break;
        case 2:
            fprintf(stdout, "utorak\n");
            break;
        case 3:
            fprintf(stdout, "sreda\n");
            break;
        case 4:
            fprintf(stdout, "cetvrtak\n");
            break;
        case 5:
            fprintf(stdout, "petak\n");
            break;
        case 6:
            fprintf(stdout, "subota\n");
            break;
    }

    exit(EXIT_SUCCESS);
}