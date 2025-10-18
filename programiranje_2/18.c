#include <stdio.h>
#include <stdlib.h>

void greska() {
    fprintf(stderr, "-1\n");
    exit(EXIT_FAILURE);
}

void print_bits(unsigned x) {

    unsigned maska = 1 << (sizeof(unsigned) * 8 - 1);
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

unsigned broj_jedinica(unsigned x) {

    unsigned brojac = 0;
    while(x) {
        brojac++;
        x = x & (x-1);
    }
    return brojac;
}

unsigned postavi_na_jedinicu(unsigned x) {

    unsigned n = broj_jedinica(x);
    if(n <= 1) {
        return x;
    }

    unsigned maska = 1;
    while(maska) {
        if((x & maska) && n >= 2) {
            n = n - 2;
            maska <<= 1;
            while((maska & x) == 0) {
                x |= maska;
                maska <<= 1;
            }
        }
        maska <<= 1;
    }
    return x;
}

int main() {

    unsigned x;
    fscanf(stdin, "%u", &x);

    unsigned y = postavi_na_jedinicu(x);
    fprintf(stdout, "%d\n", y);

    exit(EXIT_SUCCESS);
}