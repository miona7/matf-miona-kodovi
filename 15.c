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

    unsigned maska = 1 << (sizeof(unsigned)*8 - 1);
    int i = 0;
    while(maska) {
        
        if(i % 2 == 0) {
            x ^= maska;
        }
        i++;
        maska >>= 1;
    }
    return x;
}

int main() {

    unsigned x;
    fscanf(stdin, "%u", &x);

    //print_bits(x);
    unsigned y = invertovanje(x);
    fprintf(stdout, "%u\n", y);
    //print_bits(y);
    exit(EXIT_SUCCESS);
}