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
    sscanf(s, "%*s %s", m);

    if(strcmp(m, "Jan") == 0) {
        fprintf(stdout, "januar\n");
    } else if(strcmp(m, "Feb") == 0) {
        fprintf(stdout, "februar\n");
    } else if(strcmp(m, "Mar") == 0) {
        fprintf(stdout, "mart\n");
    } else if(strcmp(m, "Apr") == 0) {
        fprintf(stdout, "april\n");
    } else if(strcmp(m, "May") == 0) {
        fprintf(stdout, "maj\n");
    } else if(strcmp(m, "Jun") == 0) {
        fprintf(stdout, "jun\n");
    } else if(strcmp(m, "Jul") == 0) {
        fprintf(stdout, "jul\n");
    } else if(strcmp(m, "Aug") == 0) {
        fprintf(stdout, "avgust\n");
    } else if(strcmp(m, "Sep") == 0) {
        fprintf(stdout, "septembar\n");
    } else if(strcmp(m, "Oct") == 0) {
        fprintf(stdout, "oktobar\n");  
    } else if(strcmp(m, "Nov") == 0) {
        fprintf(stdout, "novembar\n");
    } else {
        fprintf(stdout, "decembar\n");
    }

    exit(EXIT_SUCCESS);
}