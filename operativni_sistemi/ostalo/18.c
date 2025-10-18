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

    provera_greske(argc == 3, "");

    struct stat fInfo1;
    provera_greske(stat(argv[1], &fInfo1) != -1, "");

    struct stat fInfo2;
    provera_greske(stat(argv[2], &fInfo2) != -1, "");

    mode_t pravaPristupa = 0;

    if(fInfo1.st_mode & S_IRUSR) {
        pravaPristupa |= S_IROTH;
    }
    if(fInfo1.st_mode & S_IWUSR) {
        pravaPristupa |= S_IWOTH;
    }
    if(fInfo1.st_mode & S_IXUSR) {
        pravaPristupa |= S_IXOTH;
    }

    if(fInfo1.st_mode & S_IRGRP) {
        pravaPristupa |= S_IRUSR;
    }
    if(fInfo1.st_mode & S_IWGRP) {
        pravaPristupa |= S_IWUSR;
    }
    if(fInfo1.st_mode & S_IXGRP) {
        pravaPristupa |= S_IXUSR;
    }

    if(fInfo1.st_mode & S_IROTH) {
        pravaPristupa |= S_IRGRP;
    }
    if(fInfo1.st_mode & S_IWOTH) {
        pravaPristupa |= S_IWGRP;
    }
    if(fInfo1.st_mode & S_IXOTH) {
        pravaPristupa |= S_IXGRP;
    }

    provera_greske(chmod(argv[2], pravaPristupa) != -1, "");

    exit(EXIT_SUCCESS);
}