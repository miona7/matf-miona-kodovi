#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/timeb.h>
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

    time_t t = atol(argv[1]);
    struct tm* s = localtime(&t);

    if(s->tm_hour < 10 && s->tm_min < 10) {
        fprintf(stdout, "0%d:0%d\n", s->tm_hour, s->tm_min);
    } else if(s->tm_hour < 10) {
        fprintf(stdout, "0%d:%d\n", s->tm_hour, s->tm_min);
    } else if(s->tm_min < 10) {
        fprintf(stdout, "%d:0%d\n", s->tm_hour, s->tm_min);
    } else {
        fprintf(stdout, "%d:%d\n", s->tm_hour, s->tm_min);
    }

    exit(EXIT_SUCCESS);
}