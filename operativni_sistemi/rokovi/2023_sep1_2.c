#define _XOPEN_SOURCE (700)
#include <stdio.h>
#include <stdlib.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <grp.h>
#include <pwd.h>

#define provera_greske(uslov, poruka) \
    do { \
        if(!(uslov)) { \
            fprintf(stderr, "%s\n", poruka); \
            exit(EXIT_FAILURE); \
        } \
    } while(0)

int main(int argc, char** argv) {
    
    provera_greske(argc > 1, "");

    for(int i = 1; i < argc; i++) {
        struct stat fInfo;
        int rez = stat(argv[i], &fInfo);

        if(rez != -1) {
            struct passwd* korisnik = getpwuid(fInfo.st_uid);
            if(korisnik != NULL) {
                fprintf(stdout, "%s: ", korisnik->pw_name);
              
                setgrent();
                struct group* grupa = NULL;
                while((grupa = getgrent()) != NULL) {
                    if(grupa->gr_gid == korisnik->pw_gid || grupa->gr_mem != NULL) {
                        for(char** imena = grupa->gr_mem; *imena != NULL; imena++) {
                            if(getpwnam(*imena)->pw_uid == korisnik->pw_uid) {
                                fprintf(stdout, "%s ", grupa->gr_name);
                            }
                        }
                    }
                }
                endgrent();
                fprintf(stdout, "\n");
            } 
        } else {
            fprintf(stdout, "%s: nepostojeci fajl\n", argv[i]);
        }
    }

    exit(EXIT_SUCCESS);
}