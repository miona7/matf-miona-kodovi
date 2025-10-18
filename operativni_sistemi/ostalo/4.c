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

    struct stat fInfo;
    provera_greske(stat(argv[1], &fInfo) != -1, "");
    //fprintf(stdout, "%d %d\n", (int)fInfo.st_uid ,(int)fInfo.st_gid);

    struct passwd* pwd = getpwuid(fInfo.st_uid);
    provera_greske(pwd != NULL, "");
    fprintf(stdout, "%s ", pwd->pw_name);

    struct group* grp = getgrgid(fInfo.st_gid);
    provera_greske(grp != NULL, "");
    fprintf(stdout, "%s\n", grp->gr_name);

    exit(EXIT_SUCCESS);
}