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

#define BROJ_SEK_U_DANU (24*60*60)

int main(int argc, char** argv) {
    
    provera_greske(argc == 3, "");

    time_t sekunde = atol(argv[1]);
    struct tm* vreme = localtime(&sekunde);
    provera_greske(vreme != NULL, "");

    int mesec = vreme->tm_mon;
    switch(mesec) {
        case 0:
            fprintf(stdout, "januar ");
            break;
        case 1:
            fprintf(stdout, "februar ");
            break;
        case 2:
            fprintf(stdout, "mart ");
            break;
        case 3:
            fprintf(stdout, "april ");
            break;
        case 4:
            fprintf(stdout, "maj ");
            break;
        case 5:
            fprintf(stdout, "jun ");
            break;
        case 6:
            fprintf(stdout, "jul ");
            break;
        case 7:
            fprintf(stdout, "avgust ");
            break;
        case 8:
            fprintf(stdout, "septembar ");
            break;
        case 9:
            fprintf(stdout, "oktobar ");
            break;
        case 10:
            fprintf(stdout, "novembar ");
            break;
        case 11:
            fprintf(stdout, "decembar ");
            break;
    }

    sekunde += atoi(argv[2]) * BROJ_SEK_U_DANU;
    vreme = localtime(&sekunde);
    provera_greske(vreme != NULL, "");

    mesec = vreme->tm_mon;
    switch(mesec) {
        case 0:
            fprintf(stdout, "januar\n");
            break;
        case 1:
            fprintf(stdout, "februar\n");
            break;
        case 2:
            fprintf(stdout, "mart\n");
            break;
        case 3:
            fprintf(stdout, "april\n");
            break;
        case 4:
            fprintf(stdout, "maj\n");
            break;
        case 5:
            fprintf(stdout, "jun\n");
            break;
        case 6:
            fprintf(stdout, "jul\n");
            break;
        case 7:
            fprintf(stdout, "avgust\n");
            break;
        case 8:
            fprintf(stdout, "septembar\n");
            break;
        case 9:
            fprintf(stdout, "oktobar\n");
            break;
        case 10:
            fprintf(stdout, "novembar\n");
            break;
        case 11:
            fprintf(stdout, "decembar\n");
            break;
    }

    exit(EXIT_SUCCESS);
}