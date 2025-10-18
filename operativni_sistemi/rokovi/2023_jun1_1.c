#define _XOPEN_SOURCE (700)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <dirent.h>

#define provera_greske(uslov, poruka) \
    do { \
        if(!(uslov)) { \
            fprintf(stderr, "%s\n", poruka); \
            exit(EXIT_FAILURE); \
        } \
    } while(0)

#define MAX (256)

void obidji_dir(const char* ime) {

    struct stat fInfo;
    provera_greske(lstat(ime, &fInfo) != -1, "");

    if(S_ISREG(fInfo.st_mode)) {
        char* s = strrchr(ime, '.');
        if(s != NULL && strcmp(s, ".git") == 0) {
            char tmp[MAX];
            realpath(ime, tmp);
            if(tmp != NULL) {
                s = strrchr(tmp, '/');
                if(s != NULL) {
                    int n = strlen(tmp) - strlen(s);
                    char* putanja = (char*)malloc((n + 2)*sizeof(char));
                    provera_greske(putanja != NULL, "");
                    snprintf(putanja, n + 1, "%s", tmp);
                    fprintf(stdout, "%s\n", putanja);
                }
            } else {
                provera_greske(0, "");
            }
        }
        return;
    }

    DIR* dir = opendir(ime);
    provera_greske(dir != NULL, "");

    struct dirent* dir_ent = NULL;
    while((dir_ent = readdir(dir)) != NULL) {
        char* novo_ime = (char*)malloc((strlen(ime) + strlen(dir_ent->d_name) + 2)*sizeof(char));
        provera_greske(novo_ime != NULL, "");
        sprintf(novo_ime, "%s/%s", ime, dir_ent->d_name);
        
        if(strcmp(dir_ent->d_name, ".") == 0 || strcmp(dir_ent->d_name, "..") == 0) {
            
            struct stat fInfo;
            provera_greske(stat(novo_ime, &fInfo) != -1, "");
            
            if(S_ISREG(fInfo.st_mode)) {
                char* s = strrchr(novo_ime, '.');
                if(s != NULL && strcmp(s, ".git") == 0) {
                    char tmp[MAX];
                    realpath(novo_ime, tmp);
                    if(tmp != NULL) {
                        s = strrchr(tmp, '/');
                        if(s != NULL) {
                            int n = strlen(tmp) - strlen(s);
                            char* putanja = (char*)malloc((n + 2)*sizeof(char));
                            provera_greske(putanja != NULL, "");
                            snprintf(putanja, n + 1, "%s", tmp);
                            fprintf(stdout, "%s\n", putanja);
                        }
                    } else {
                        provera_greske(0, "");
                    }
                }
            }

            free(novo_ime);
            continue;
        }
        obidji_dir(novo_ime);
        free(novo_ime);
    }

    provera_greske(closedir(dir) != -1, "");
}

int main(int argc, char** argv) {
    
    provera_greske(argc == 2, "");

    struct stat fInfo;
    provera_greske(stat(argv[1], &fInfo) != -1, "");
    provera_greske(S_ISDIR(fInfo.st_mode), "");

    obidji_dir(argv[1]);

    exit(EXIT_SUCCESS);
}