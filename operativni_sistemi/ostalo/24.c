#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>
#include <dirent.h>

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

    provera_greske(strcmp(argv[1], argv[2]) != 0, "Apsolutne putanje fajlova su iste");
    struct stat fInfo;
    provera_greske(stat(argv[1], &fInfo) != -1, "");
    
    if(S_ISDIR(fInfo.st_mode)) {
        pid_t dete_pid = fork();
        provera_greske(dete_pid != -1, "");
        if(dete_pid == 0) {
            provera_greske(execlp("mv", "mv", argv[1], argv[2], NULL) != -1, "");
        }
        
        int status = 0;
        provera_greske(wait(&status) != -1, "");
        if(WIFEXITED(status) && (WEXITSTATUS(status) == EXIT_SUCCESS)) {
            fprintf(stdout, "pomera se direktorijum %s u %s\n", argv[1], argv[2]);
        } else {
            provera_greske(0, "");
        }
    } else {
        pid_t dete_pid = fork();
        provera_greske(dete_pid != -1, "");
        if(dete_pid == 0) {
            provera_greske(execlp("mv", "mv", argv[1], argv[2], NULL) != -1, "");
        }
        
        int status = 0;
        provera_greske(wait(&status) != -1, "");
        if(WIFEXITED(status) && (WEXITSTATUS(status) == EXIT_SUCCESS)) {
            fprintf(stdout, "pomera regularni fajl %s u %s\n", argv[1], argv[2]);
        } else {
            provera_greske(0, "");
        }
    }

    exit(EXIT_SUCCESS);
}