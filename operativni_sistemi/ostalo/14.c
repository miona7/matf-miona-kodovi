#define _XOPEN_SOURCE 700
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
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

    struct stat finfo;
    provera_greske(lstat(argv[1], &finfo) != -1, "");

    struct passwd* pwd = getpwuid(finfo.st_uid);
    provera_greske(pwd != NULL, "");

    struct group* grp = getgrgid(finfo.st_gid);
    provera_greske(grp != NULL, "");

    if(strcmp(pwd->pw_name, grp->gr_name) == 0) {
        fprintf(stdout, "da\n");
    }
    else {
        fprintf(stdout, "ne\n");
    }

    exit(EXIT_SUCCESS);
}