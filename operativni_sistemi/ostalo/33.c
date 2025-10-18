#define _XOPEN_SOURCE (700)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <ftw.h>
#include <fcntl.h>

#define MAX (50)
#define FLAGS (0)
#define SEKUNDE_U_DANU (24*60*60)
#define MAX_BAF (1024)
#define DOZVOLJENA_MODIFIKACIJA (30)

#define provera_greske(uslov, poruka) \
    do { \
        if(!(uslov)) { \
            fprintf(stderr, "%s\n", poruka); \
            exit(EXIT_FAILURE); \
        } \
    } while(0)

const char* ime = NULL;

void napravi_dir(const char* ime) {

    mode_t prava_pristupa = 0777;
    provera_greske(mkdir(ime, prava_pristupa) != -1, "");
    provera_greske(chmod(ime, prava_pristupa) != -1, "");
}

bool osIsPublicFile(const char* fpath) {

    struct stat fInfo;
    provera_greske(stat(fpath, &fInfo) != -1, "");
    
    provera_greske(S_ISREG(fInfo.st_mode), "");

    if((fInfo.st_mode & S_IROTH) && (fInfo.st_mode & S_IWOTH)) {
        return true;
    }
    else {
        return false;
    }
}

unsigned osNumOfDaysFileModified(const char *fpath) {
    
    time_t vreme_sad = time(NULL);
    struct stat fInfo;
    provera_greske(stat(fpath, &fInfo) != -1, "");

    return (unsigned)(vreme_sad - fInfo.st_mtime)/SEKUNDE_U_DANU;
}

void osMoveFile(const char* srcPath, const char* destPath) {

    struct stat fInfo;
    provera_greske(stat(srcPath, &fInfo) != -1, "");

    int fdSrc = open(srcPath, O_RDONLY);
    provera_greske(fdSrc != -1, "");

    int fdDest = open(destPath, O_WRONLY | O_CREAT | O_TRUNC);
    provera_greske(fdDest != -1, "");

    int procitano = 0;
    char bafer[MAX_BAF];
    while((procitano = read(fdSrc, bafer, MAX_BAF)) > 0) {
        provera_greske(write(fdDest, bafer, procitano) != -1, "");
    }
    provera_greske(procitano != -1, "");

    close(fdSrc);
    close(fdDest);

    provera_greske(unlink(srcPath) != -1, "");
    provera_greske(chmod(destPath, fInfo.st_mode) != -1, "");
}

int obidji_dir(const char* putanja, const struct stat* sb, int typeflag, struct FTW* ftwbuf) {
    
    if(osIsPublicFile(putanja)) {
        if(osNumOfDaysFileModified(putanja) < DOZVOLJENA_MODIFIKACIJA) {
            osMoveFile(putanja, ime);
        } else {
            provera_greske(unlink(putanja) != -1, "");
        }
    }
    
    return 0;
} 

int main(int argc, char** argv) {

    provera_greske(argc == 3, "");

    napravi_dir(argv[2]);

    struct stat fInfo;
    provera_greske(stat(argv[1], &fInfo) != -1, "");
    provera_greske(S_ISDIR(fInfo.st_mode), "");  

    provera_greske(nftw(argv[1], obidji_dir, MAX, FLAGS) != -1, "");

    exit(EXIT_SUCCESS);
}