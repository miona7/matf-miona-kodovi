#define _XOPEN_SOURCE (700)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <dirent.h>

#define proveri_greske(uslov, poruka) \
    do { \
        if(!(uslov)) { \
            fprintf(stderr, "%s\n", poruka); \
            exit(EXIT_FAILURE); \
        } \
    } while(0)

#define MAX (256)

void obidji_dir(char* putanja) {

    struct stat fInfo;
    proveri_greske(lstat(putanja, &fInfo) != -1, "");

    if(S_ISREG(fInfo.st_mode)) {
        char* s = strrchr(putanja, '.');
        if(s != NULL && strcmp(s, ".git") == 0) {
            char tmp[MAX];
            realpath(putanja, tmp);
            if(tmp != NULL) {
                s = strrchr(tmp, '/');
                if(s != NULL) {
                    char* ispis = (char*)malloc((strlen(tmp) - strlen(s) + 2) * sizeof(char));
                    proveri_greske(ispis != NULL, "");
                    snprintf(ispis, strlen(tmp) - strlen(s) + 1, "%s", tmp);
                    fprintf(stdout, "%s\n", ispis);
                }
            }
        }
        return;
    }

    DIR* dir = opendir(putanja);
    proveri_greske(dir != NULL, "");

    struct dirent* dir_ent = NULL;
    while((dir_ent = readdir(dir)) != NULL) {
        char* nova_putanja = (char*)malloc((strlen(putanja) + strlen(dir_ent->d_name) + 2) * sizeof(char));
        proveri_greske(nova_putanja != NULL, "");
        sprintf(nova_putanja, "%s/%s", putanja, dir_ent->d_name);

        if(strcmp(dir_ent->d_name, ".") == 0 || strcmp(dir_ent->d_name, "..") == 0) {
            
            struct stat fInfo;
            proveri_greske(stat(nova_putanja, &fInfo) != -1, "");
            if(S_ISREG(fInfo.st_mode)) {
                char* t = strrchr(nova_putanja, '.');
                if(t != NULL && strcmp(t, ".git") == 0) {
                    char tmp[MAX];
                    realpath(nova_putanja, tmp);
                    if(tmp != NULL) {
                        t = strrchr(tmp, '/');
                        if(t != NULL) {
                            char* ispis = (char*)malloc((strlen(tmp) - strlen(t) + 2) * sizeof(char));
                            proveri_greske(ispis != NULL, "");
                            snprintf(ispis, strlen(tmp) - strlen(t) + 1, "%s", tmp);
                            fprintf(stdout, "%s\n", ispis);
                        }
                    }
                }
            }

            free(nova_putanja);
            continue;
        }

        obidji_dir(nova_putanja);
        free(nova_putanja);
    }

    proveri_greske(closedir(dir) != -1, "");
}

int main(int argc, char** argv) {

    proveri_greske(argc == 2, "");

    struct stat fInfo;
    proveri_greske(stat(argv[1], &fInfo) != -1, "");
    proveri_greske(S_ISDIR(fInfo.st_mode), "");

    obidji_dir(argv[1]);

    exit(EXIT_SUCCESS);
}