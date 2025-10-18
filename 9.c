#include <stdio.h>
#include <stdlib.h>
#define MIN 1

void greska() {
    fprintf(stderr, "-1\n");
    exit(EXIT_FAILURE);
}

void print_bits(int x) {
    unsigned maska = 1 << (sizeof(int)*8 - 1);
    while(maska) {
        if(maska & x) {
            putchar('1');
        }
        else {
            putchar('0');
        }
        maska >>= 1;
    }
    putchar('\n');
}

int izracunaj_broj_jedinica(int x, int k) {

    unsigned maska = ~(~0 << k);
    //print_bits(maska);
    int brojac = 0;

    while(x) {
        if((maska & x) == maska) {
            brojac++;
        }
        x >>= 1;
    }
    return brojac;
}

int main() {

    int x, k;
    fscanf(stdin, "%d%d", &x, &k);
    if(x < MIN || k < MIN) {
        greska();
    }
    //print_bits(x);

    fprintf(stdout, "%d\n", izracunaj_broj_jedinica(x, k));

    exit(EXIT_SUCCESS);
}