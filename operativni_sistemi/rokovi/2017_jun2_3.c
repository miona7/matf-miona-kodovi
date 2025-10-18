#define _XOPEN_SOURCE (700)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

#define provera_greske(uslov, poruka) \
    do { \
        if(!(uslov)) { \
            fprintf(stderr, "%s\n", poruka); \
            exit(EXIT_FAILURE); \
        } \
    } while(0)

#define MAX (257)

int main(int argc, char** argv) {
    
    provera_greske(argc == 4, "");

    struct stat fInfo;
    provera_greske(stat(argv[1], &fInfo) != -1, "");

    /*char* rec1 = (char*)malloc((strlen(argv[2]) + 1) * sizeof(char));
    provera_greske(rec1 != NULL, "");
    
    
    char* rec2 = (char*)malloc((strlen(argv[3]) + 1) * sizeof(char));
    provera_greske(rec2 != NULL, "");*/


    int fd = open(argv[1], O_RDWR);
    provera_greske(fd != -1, "");

    FILE* ulaz = fdopen(fd, "r+");
    provera_greske(ulaz != NULL, "");

    char rec[MAX]; int brojac = 0;
    while(fscanf(ulaz, "%s", rec) == 1) {
        if(strcmp(rec, argv[2]) == 0) {
            struct flock katanac;
            katanac.l_type = F_WRLCK;
            katanac.l_whence = SEEK_SET;
            katanac.l_start = ftell(ulaz);
            katanac.l_len = -strlen(rec);

            int rez = fcntl(fd, F_SETLK, &katanac);
            if(rez == -1) {
                if(errno != EACCES && errno != EAGAIN) {
                    provera_greske(0, "");
                } else {
                    brojac++;
                }
            } else {
                provera_greske(fseek(ulaz, -strlen(rec), SEEK_CUR) != (off_t)-1, "");
                fprintf(ulaz, "%s", argv[3]);
                katanac.l_type = F_UNLCK;
                provera_greske(fcntl(fd, F_SETLK, &katanac) != -1, "");
            }
        }
    }

    fprintf(stdout, "%d\n", brojac);

    fclose(ulaz);
    exit(EXIT_SUCCESS);
}