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
#include <pwd.h>
#include <grp.h>

#define provera_greske(uslov, poruka) \
    do { \
        if(!(uslov)) { \
            fprintf(stderr, "%s\n", poruka); \
            exit(EXIT_FAILURE); \
        } \
    } while(0)

int main(int argc, char** argv) {

    provera_greske(argc == 2, "");

    struct stat f_info;
    provera_greske(lstat(argv[1], &f_info) != -1, "");

    struct passwd* korisnik = getpwuid(f_info.st_uid);
    provera_greske(korisnik != NULL, "");

    struct group* grupa = getgrgid(f_info.st_gid);
    provera_greske(grupa != NULL, "");

    fprintf(stdout, "%s %s\n", korisnik->pw_name, grupa->gr_name);

    exit(EXIT_SUCCESS);
}
