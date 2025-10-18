#define _XOPEN_SOURCE (700)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <sys/mman.h>
#include <unistd.h>
#include <fcntl.h>
#include <dirent.h>
#include <errno.h>
#include <pthread.h>
#include <semaphore.h>

#define provera_greske(uslov, poruka) \
    do { \
        if(!(uslov)) { \
            fprintf(stderr, "%s\n", poruka); \
            exit(EXIT_FAILURE); \
        } \
    } while(0)

#define provera_greske_niti(gr, poruka) \
    do { \
        int greska = gr; \
        if(greska) { \
            errno = greska; \
            provera_greske(0, poruka); \
        } \
    } while(0)

#define MAX (256)

int main(int argc, char** argv) {

    provera_greske(argc == 3, "");

    int fd = open(argv[1], O_RDWR);
    provera_greske(fd != -1, "");

    FILE* ulaz = fdopen(fd, "r+");
    provera_greske(ulaz != NULL, "");

    FILE* izlaz = fopen(argv[2], "w");
    provera_greske(izlaz != NULL, "");

    char* linija = NULL;
    size_t n = 0;
    int brojac = 0;

    while(getline(&linija, &n, ulaz) > 0) {

        struct flock katanac;
        katanac.l_type = F_WRLCK;
        katanac.l_start = ftell(ulaz);
        katanac.l_whence = SEEK_SET;
        katanac.l_len = strlen(linija);

        int rez = fcntl(fd, F_GETLK, &katanac);

        if(rez == -1) {
            if(errno != EACCES && errno != EAGAIN) {
                provera_greske(0, "");
            }
        } else {
            fprintf(izlaz, "%s", linija);
            katanac.l_type = F_UNLCK;
            provera_greske(fcntl(fd, F_SETLK, &katanac) != -1, "");
            brojac++;
        }
    }

    fprintf(stdout, "%d\n", brojac);
    free(linija);
    fclose(ulaz);
    fclose(izlaz);
    exit(EXIT_SUCCESS);
}
