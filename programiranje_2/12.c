#include <stdio.h>
#include <stdlib.h>
#define MIN 1

void greska() {
    fprintf(stderr, "-1\n");
    exit(EXIT_FAILURE);
}

void print_bits(unsigned x) {
    unsigned maska = 1 << (sizeof(unsigned)*8 - 1);
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

unsigned invertovanje(unsigned x) {

    unsigned maska = 1;
    int i; int brojac = 1;
    for(i = 0; i < sizeof(unsigned)*8; i++, maska <<= 1) {
        
        if(brojac % 3 == 0 || brojac % 4 == 0) {
            x ^= maska;
        }

        if(brojac == 4) {
            brojac = 1;
        }
        else {
            brojac++;
        }
    }
    return x;
}

int main() {

    unsigned x;
    fscanf(stdin, "%x", &x);

    //print_bits(x);
    unsigned y = invertovanje(x);
    fprintf(stdout, "0x%x\n", y);
    //print_bits(y);
    exit(EXIT_SUCCESS);
}