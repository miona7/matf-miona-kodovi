#include <stdio.h>
#include <stdlib.h>

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

int main(int argc, char** argv) {

    provera_greske(argc == 2, "");

    struct stat fInfo;
    provera_greske(stat(argv[1], &fInfo) != -1, "");

    mode_t pravaPristupa = 0;

    if(fInfo.st_mode & S_IRUSR) {
        pravaPristupa |= S_IROTH;
    }
    if(fInfo.st_mode & S_IWUSR) {
        pravaPristupa |= S_IWOTH;
    }
    if(fInfo.st_mode & S_IXUSR) {
        pravaPristupa |= S_IXOTH;
    }

    if(fInfo.st_mode & S_IRGRP) {
        pravaPristupa |= S_IRUSR;
    }if(fInfo.st_mode & S_IWGRP) {
        pravaPristupa |= S_IWUSR;
    }if(fInfo.st_mode & S_IXGRP) {
        pravaPristupa |= S_IXUSR;
    }

    if(fInfo.st_mode & S_IROTH) {
        pravaPristupa |= S_IRGRP;
    }
    if(fInfo.st_mode & S_IWOTH) {
        pravaPristupa |= S_IWGRP;
    }
    if(fInfo.st_mode & S_IXOTH) {
        pravaPristupa |= S_IXGRP;
    }

    provera_greske(chmod(argv[1], pravaPristupa) != -1, "");

    exit(EXIT_SUCCESS);
}