#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

#define provera_greske(uslov, poruka) \
    do { \
        if(!(uslov)) { \
            fprintf(stderr, "%s\n", poruka); \
            exit(EXIT_FAILURE); \
        } \
    } while(0)

#define MAX (255)

bool jeste_otkljucana(int fd, int pocetak, int duzina) {
    struct flock katanac;
    katanac.l_type = F_WRLCK;
    katanac.l_whence = SEEK_SET;
    katanac.l_start = pocetak;
    katanac.l_len = duzina;

    provera_greske(fcntl(fd, F_GETLK, &katanac) != -1, "");
    
    if(katanac.l_type == F_UNLCK) {
        return true;
    } else {
        return false;
    }
}

char* obrni(char* rec, int n) {
    char* obrnuta = (char*)malloc((n+1)*sizeof(char));
    provera_greske(obrnuta != NULL, "");

    int i;
    for(int i = 0, j = n-1; j >= 0; i++, j--) {
        obrnuta[i] = rec[j];
    }
    obrnuta[i] = '\0';

    return obrnuta;
}

void upisi(int fd, int pocetak, char* rec, int n) {
    provera_greske(lseek(fd, pocetak, SEEK_SET) != (off_t)-1, "");
    provera_greske(write(fd, rec, n) != -1, "");
    provera_greske(lseek(fd, 1, SEEK_CUR) != (off_t)-1, "");
}

int main(int argc, char** argv) {
    
    provera_greske(argc == 2, "");

    int fd = open(argv[1], O_RDWR);
    provera_greske(fd != -1, "");

    char bafer[MAX+1];
    int i = 0;
    int fajl_pt = 0;
    int pocetak_reci = 0;
    int uspeh = 0;
    int neuspeh = 0;
    char c;

    while(read(fd, &c, 1) > 0) {
        if(c == ' ' || c == '\n') {
            bafer[i] = '\0';
            if(jeste_otkljucana(fd, pocetak_reci, strlen(bafer))) {
                char* obrnuta = obrni(bafer, strlen(bafer));
                upisi(fd, pocetak_reci, obrnuta, strlen(bafer));
                free(obrnuta);
                uspeh++;
            } else {
                neuspeh++;
            }
            pocetak_reci = fajl_pt+1;
            i = 0;
        } else {
            bafer[i++] = c;
        }
        fajl_pt++;
    }

    fprintf(stdout, "%d %d\n", uspeh, neuspeh);
    close(fd);
    exit(EXIT_SUCCESS);
}