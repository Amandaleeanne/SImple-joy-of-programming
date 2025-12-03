#include <stdio.h>
#include <stdlib.h>

int adder_register[20];
int memory[1000];


int main(int argc, char const *argv[])
{
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <file>\n", argv[0]);
        return 1;
    }

    FILE *input = fopen(argv[1], "r");
    if (input == NULL) {
        perror("Error opening file");
        return 1;
    }

    
    

    

    fclose(input);
    return 0;
}
