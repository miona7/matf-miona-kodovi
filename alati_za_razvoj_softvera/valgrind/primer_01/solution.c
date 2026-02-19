#include <stdlib.h>

int main() {
    char* string = malloc(5 * sizeof(char)); 
    free(string);
    return 0;
}