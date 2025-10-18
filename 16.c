#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MIN 1
#define MAX 21 

void greska() {
    fprintf(stderr, "-1\n");
    exit(EXIT_FAILURE);
}

int uporedi(const void* a, const void* b) {
    
    return *((int*)a) - *((int*)b);
}

int main(int argc, char** argv) {

    if(argc != 3) {
        greska();
    }

    FILE* ulaz = fopen(argv[1], "r");
    if(ulaz == NULL) {
        greska();
    }
    int x = atoi(argv[2]);

    int n;
    fscanf(ulaz, "%d", &n);
    if(n < MIN) {
        greska();
    }

    int* a = (int*)malloc(n * sizeof(int));
    if(a == NULL) {
        greska();
    }

    int i;
    for(i = 0; i < n; i++) {
        fscanf(ulaz, "%d", &a[i]);
    }

    qsort(a, n, sizeof(int), uporedi);

    for(i = n - 1; i >= 0; i--) {
        if(a[i] <= x) {
            fprintf(stdout, "%d ", a[i]);
        }
    }

    //qsort(a, n, sizeof(int), uporedi);

    for(i = 0; i < n; i++) {
        if(a[i] > x) {
            fprintf(stdout, "%d ", a[i]);
        }
    }
    fprintf(stdout, "\n");

    free(a);
    fclose(ulaz);
    exit(EXIT_SUCCESS);
}