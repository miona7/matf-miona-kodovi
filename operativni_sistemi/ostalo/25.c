#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

#define MAX (1024)

#define provera_greske(uslov, poruka) \
    do { \
        if(!(uslov)) { \
            fprintf(stderr, "%s\n", poruka); \
            exit(EXIT_FAILURE); \
        } \
    } while(0)

int main(int argc, char** argv) {

    provera_greske(argc == 3, "");

    FILE* ulaz = fopen(argv[1], "r");
    provera_greske(ulaz != NULL, "");

    int fd = open(argv[2], O_RDWR | O_CREAT);
    provera_greske(fd != -1, "");

    char linija[MAX];
    while(fgets(linija, MAX-1, ulaz) != NULL) {
        off_t pozicija; char rec[MAX]; char c;
        sscanf(linija, "%jd%c%s", &pozicija, &c, rec);
        provera_greske(lseek(fd, pozicija, SEEK_SET) != (off_t)-1, "");
        provera_greske(write(fd, rec, strlen(rec)) != -1, "");
    }

    close(fd);
    exit(EXIT_SUCCESS);
}