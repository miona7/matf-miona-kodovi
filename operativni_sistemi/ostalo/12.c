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

    struct stat fInfo;
    provera_greske(stat(argv[1], &fInfo) != -1, "Nepostojeci fajl");

    mode_t pravaPristupa = 0;

    if(argv[2][0] == 'u') {
        if(argv[2][1] == '+') {
            if(argv[2][2] == 'r') {
                pravaPristupa |= S_IRUSR;
            }
            else if(argv[2][2] == 'w') {
                pravaPristupa |= S_IWUSR;
            }
            else if(argv[2][2] == 'x') {
                pravaPristupa |= S_IXUSR;
            }
            else {
                provera_greske(0, "");
            }
        }
        else if(argv[2][1] == '-') {
            if(argv[2][2] != 'r') {
                pravaPristupa |= S_IRUSR;
            }
            else if(argv[2][2] != 'w') {
                pravaPristupa |= S_IWUSR;
            }
            else if(argv[2][2] != 'x') {
                pravaPristupa |= S_IXUSR;
            }
            else {
                provera_greske(0, "");
            }
        }
        else {
            provera_greske(0, "");
        }
        
        if(fInfo.st_mode & S_IRGRP) {
            pravaPristupa |= S_IRGRP;
        }
        if(fInfo.st_mode & S_IWGRP) {
            pravaPristupa |= S_IWGRP;
        }
        if(fInfo.st_mode & S_IXGRP) {
            pravaPristupa |= S_IXGRP;
        }

        if(fInfo.st_mode & S_IROTH) {
            pravaPristupa |= S_IROTH;
        }
        if(fInfo.st_mode & S_IWOTH) {
            pravaPristupa |= S_IWOTH;
        }
        if(fInfo.st_mode & S_IXOTH) {
            pravaPristupa |= S_IXOTH;
        }
    }
    else if(argv[2][0] == 'g') {
        if(argv[2][1] == '+') {
            if(argv[2][2] == 'r') {
                pravaPristupa |= S_IRGRP;
            }
            else if(argv[2][2] == 'w') {
                pravaPristupa |= S_IWGRP;
            }
            else if(argv[2][2] == 'x') {
                pravaPristupa |= S_IXGRP;
            }
            else {
                provera_greske(0, "");
            }
        }
        else if(argv[2][1] == '-') {
            if(argv[2][2] != 'r') {
                pravaPristupa |= S_IRGRP;
            }
            else if(argv[2][2] != 'w') {
                pravaPristupa |= S_IWGRP;
            }
            else if(argv[2][2] != 'x') {
                pravaPristupa |= S_IXGRP;
            }
            else {
                provera_greske(0, "");
            }
        }
        else {
            provera_greske(0, "");
        }

        if(fInfo.st_mode & S_IRUSR) {
            pravaPristupa |= S_IRUSR;
        }
        if(fInfo.st_mode & S_IWUSR) {
            pravaPristupa |= S_IWUSR;
        }
        if(fInfo.st_mode & S_IXUSR) {
            pravaPristupa |= S_IXUSR;
        }

        if(fInfo.st_mode & S_IROTH) {
            pravaPristupa |= S_IROTH;
        }
        if(fInfo.st_mode & S_IWOTH) {
            pravaPristupa |= S_IWOTH;
        }
        if(fInfo.st_mode & S_IXOTH) {
            pravaPristupa |= S_IXOTH;
        }
    }
    else if(argv[2][0] == 'o') {
        if(argv[2][1] == '+') {
            if(argv[2][2] == 'r') {
                pravaPristupa |= S_IROTH;
            }
            else if(argv[2][2] == 'w') {
                pravaPristupa |= S_IWOTH;
            }
            else if(argv[2][2] == 'x') {
                pravaPristupa |= S_IXOTH;
            }
            else {
                provera_greske(0, "");
            }
        }
        else if(argv[2][1] == '-') {
            if(argv[2][2] != 'r') {
                pravaPristupa |= S_IROTH;
            }
            else if(argv[2][2] != 'w') {
                pravaPristupa |= S_IWOTH;
            }
            else if(argv[2][2] != 'x') {
                pravaPristupa |= S_IXOTH;
            }
            else {
                provera_greske(0, "");
            }
        }
        else {
            provera_greske(0, "");
        }
        
        if(fInfo.st_mode & S_IRUSR) {
            pravaPristupa |= S_IRUSR;
        }
        if(fInfo.st_mode & S_IWUSR) {
            pravaPristupa |= S_IWUSR;
        }
        if(fInfo.st_mode & S_IXUSR) {
            pravaPristupa |= S_IXUSR;
        }

        if(fInfo.st_mode & S_IRGRP) {
            pravaPristupa |= S_IRGRP;
        }
        if(fInfo.st_mode & S_IWGRP) {
            pravaPristupa |= S_IWGRP;
        }
        if(fInfo.st_mode & S_IXGRP) {
            pravaPristupa |= S_IXGRP;
        }
    }
    else {
        provera_greske(0, "");
    }
    
    provera_greske(chmod(argv[1], pravaPristupa) != -1, "");
    exit(EXIT_SUCCESS);
}