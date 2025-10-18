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
    
    provera_greske(argc == 2, "");

    time_t sekunde = atol(argv[1]);
    struct tm* vreme = localtime(&sekunde);
    provera_greske(vreme != NULL, "");

    int sati = vreme->tm_hour;

    if(sati >= 0 && sati < 7) {
        fprintf(stdout, "noc\n");
    } else if(sati >= 7 && sati < 9) {
        fprintf(stdout, "jutro\n");
    } else if(sati >= 9 && sati < 12) {
        fprintf(stdout, "prepodne\n");
    } else if(sati >= 12 && sati < 19) {
        fprintf(stdout, "popodne\n");
    } else {
        fprintf(stdout, "vece\n");
    }

    exit(EXIT_SUCCESS);
}