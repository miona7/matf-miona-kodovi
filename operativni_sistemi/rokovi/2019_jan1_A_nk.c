#define _XOPEN_SOURCE (700)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>
#include <dirent.h>
#include <fcntl.h>
#include <libgen.h>

#define provera_greske(uslov, poruka) \
    do { \
        if(!(uslov)) { \
            perror(poruka); \
            fprintf(stderr, "%s\n", poruka); \
            exit(EXIT_FAILURE); \
        } \
    } while(0)

char* stara_ext = NULL;
char* nova_ext = NULL;

void obidji_dir(char* putanja) {

    struct stat fInfo;
    provera_greske(lstat(putanja, &fInfo) != -1, "");

    if(S_ISREG(fInfo.st_mode)) {
        char* s = strrchr(putanja, '.');
        if(s != NULL) {
            if(strcmp(s, stara_ext) == 0) {
                int putanja_duzina = strlen(putanja);
                int ext_duzina = strlen(stara_ext);
                char* novo_ime = malloc(strlen(putanja) + strlen(nova_ext) + 1);
                strncpy(novo_ime, putanja, putanja_duzina - ext_duzina);
                strcat(novo_ime, nova_ext);

                pid_t dete_pid = fork();
                provera_greske(dete_pid != -1, "");
                if(dete_pid == 0) {
                    provera_greske(execlp("mv", "mv", putanja, novo_ime, NULL) != -1, "");
                }
                provera_greske(wait(NULL) != -1, "");
                //provera_greske(rename(putanja, novo_ime) != -1, "");
            }
        }
        return;
    }

    DIR* dir_ent = opendir(putanja);
    provera_greske(dir_ent != NULL, "");

    struct dirent* dir = NULL;
    while((dir = readdir(dir_ent)) != NULL) {
        char* nova_putanja = (char*)malloc((strlen(putanja) + strlen(dir->d_name) + 2) * sizeof(char));
        provera_greske(nova_putanja != NULL, "");
        sprintf(nova_putanja, "%s/%s", putanja, dir->d_name);

        if(strcmp(dir->d_name, ".") == 0 || strcmp(dir->d_name, "..") == 0) {
            
            provera_greske(stat(nova_putanja, &fInfo) != -1, "");
            if(S_ISREG(fInfo.st_mode)) {
                char* t = strrchr(nova_putanja, '.');
                if(t != NULL) {
                    if(strcmp(t, stara_ext) == 0) {
                        int putanja_duzina = strlen(nova_putanja);
                        int ext_duzina = strlen(stara_ext);
                        char* novo_ime = malloc(strlen(nova_putanja) + strlen(nova_ext) + 1);
                        strncpy(novo_ime, nova_putanja, putanja_duzina - ext_duzina);
                        strcat(novo_ime, nova_ext);
                        
                        pid_t dete_pid = fork();
                        provera_greske(dete_pid != -1, "");
                        if(dete_pid == 0) {
                            provera_greske(execlp("mv", "mv", putanja, novo_ime, NULL) != -1, "");
                        }
                        provera_greske(wait(NULL) != -1, "");
                    }         
                }
            }
            
            free(nova_putanja);
            continue;
        }

        obidji_dir(nova_putanja);
        free(nova_putanja);
    }

    provera_greske(closedir(dir_ent) != -1, "");
}

int main(int argc, char** argv) {
    
    provera_greske(argc == 4, "");

    struct stat fInfo;
    provera_greske(stat(argv[1], &fInfo) != -1, "");
    provera_greske(S_ISDIR(fInfo.st_mode), "");

    stara_ext = argv[2];
    nova_ext = argv[3];

    obidji_dir(argv[1]);

    exit(EXIT_SUCCESS);
}