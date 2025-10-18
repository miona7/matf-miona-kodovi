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

#define ZAKLJUCAJ (0)
#define OTKLJUCAJ (1)
#define MAX (256)

bool jeste_poz_4cif_br(int x) {
    return x >= 1000 && x <= 9999;
}

bool uspesnoZakljucan(int fd, int pocetak, int duzina, int mod) {

    struct flock katanac;
    katanac.l_type = F_WRLCK;
    katanac.l_whence = SEEK_SET;
    katanac.l_start = pocetak;
    katanac.l_len = duzina;

    if(mod == ZAKLJUCAJ) {
        if(fcntl(fd, F_SETLK, &katanac) != -1) {
            return true;
        } else {
            return false;
        }
    } else {
        katanac.l_type = F_UNLCK;
        if(fcntl(fd, F_SETLK, &katanac) != -1) {
            return true;
        } else {
            return false;
        }
    }
}

int mod(int fd, int pocetak, int duzina) {
    
    off_t rez_seek = lseek(fd, -5, SEEK_CUR);
    provera_greske(rez_seek != (off_t)-1, "");
    
    /*if(rez_seek == (off_t)-1) {
        return -1;
    }*/

    char tmp[4] = "####";
    int wr_rez = write(fd, tmp, 4);
    if(wr_rez == -1) {
        provera_greske(lseek(fd, 5, SEEK_CUR) != (off_t)-1, "");
        return -2;
    }

    provera_greske(lseek(fd, 1, SEEK_CUR) != (off_t)-1, "");
    return 0;
}

int main(int argc, char** argv) {

    provera_greske(argc == 2, "");

    int fd = open(argv[1], O_RDWR);
    provera_greske(fd != -1, "");

    char bafer[MAX + 1];
    int i = 0;
    int pocetak = 0;
    int fajl_pocetak = 0;    
    char c;
    while(read(fd, &c, 1) > 0) {

        if(c == ' ' || c == '\n') {
            bafer[i] = '\0';
            int x = atoi(bafer);
            if(jeste_poz_4cif_br(x)) {
                int duzina = strlen(bafer);
                if(uspesnoZakljucan(fd, pocetak, duzina, ZAKLJUCAJ)) {
                    int mod_rez = mod(fd, pocetak, duzina);
                    //provera_greske(mod_rez != -1, "");
                    //provera_greske(mod_rez != -2, "");
                }
            }
            pocetak = fajl_pocetak+1;
            i = 0;
        } else {
            bafer[i++] = c;
        }
        fajl_pocetak++;
    }

    close(fd);
    exit(EXIT_SUCCESS);
}