#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#define SEK_U_MIN (60)
#define GOD (1900)
#define MESEC (1)

#define provera_greske(uslov, poruka) \
    do { \
        if(!(uslov)) { \
            fprintf(stderr, "%s\n", poruka); \
            exit(EXIT_FAILURE); \
        } \
    } while(0)

int main(int argc, char** argv) {
    
    provera_greske(argc == 3, "");

    time_t t = atol(argv[1]) + atoi(argv[2])*SEK_U_MIN;
    struct tm* s = localtime(&t);
    provera_greske(s != NULL, "");
    
    if(s->tm_mday < 10 && s->tm_mon+MESEC < 10) {
        fprintf(stdout, "0%d/0%d/%d ", s->tm_mday, s->tm_mon+MESEC, s->tm_year+GOD);
    } else if(s->tm_mday < 10) {
        fprintf(stdout, "0%d/%d/%d ", s->tm_mday, s->tm_mon+MESEC, s->tm_year+GOD);
    } else if(s->tm_mon+MESEC < 10) {
        fprintf(stdout, "%d/0%d/%d ", s->tm_mday, s->tm_mon+MESEC, s->tm_year+GOD);
    } else {
        fprintf(stdout, "%d/%d/%d ", s->tm_mday, s->tm_mon+MESEC, s->tm_year+GOD);
    }

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