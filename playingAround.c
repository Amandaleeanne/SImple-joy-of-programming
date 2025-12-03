#include <stdio.h>
#include <stdlib.h>


int adder_register[20];
int memory[1000];
char opcode_map[6][4] = {
    "INP",
    "OUT",
    "ADD",
    "SUB",
    "MUL",
    "DIV",
};
int main(int argc, char const *argv[])
{
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <file>\n", argv[0]);
        return 1;
    }

    FILE *input = fopen(argv[1], "r");
    FILE *output = fopen("out.txt", "w");
    if (input == NULL || output == NULL) {
        perror("Error opening file");
        return 1;
    }
    // For input
    int operation;
    int mode;
    int operand; 
    char output_line[14]; //I_INP 8000.00\0
    fscanf(input, "%2d %1d %6d", &operation, &mode, &operand) == 3;
        // Process the read values
        printf("Operation: %d, Mode: %d, Operand: %d\n", operation, mode, operand);
        //first we want to check the mode to see if the read value is immediate or memory
        if (mode == 0) {
            output_line[0] = 'I'; // Memory mode
        } else {
            output_line[0] = 'M'; // Immediate mode
        }
        output_line[1] = '_'; // Separator
        // Now we get the opcode string
        snprintf(&output_line[2], 4, "%s", opcode_map[operation]);
        // Now we format the operand to be 6 digits with leading zeros  
        snprintf(&output_line[5], 7, "%06d", operand);
    fprintf(output, "%s\n", output_line);
    printf("Finished reading file, check out.\n");
    fclose(input);
    fclose(output);
    return 0;
}
