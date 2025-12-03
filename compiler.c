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
    char output_line[32]; //I_INP 8000.00\0
    while (fscanf(input, "%2d %1d %6d", &operation, &mode, &operand) == 3)
    {
        // Process the read values
        printf("Operation: %d, Mode: %d, Operand: %d\n", operation, mode, operand);

        // Validate operation bounds
        if (operation < 0 || operation > 5) {
            fprintf(stderr, "Error: operation code %d out of bounds (0-5). Skipping line.\n", operation);
            continue;
        }

        if (mode < 0 || mode > 1) {
            fprintf(stderr, "Error: mode %d out of bounds (0-1). Skipping line.\n", mode);
            continue;
        }

        //first we want to check the mode to see if the read value is immediate or memory
        if (mode == 1) {output_line[0] = 'M'; } // Memory mode
            output_line[0] = 'I'; // Immediate mode (default)

        output_line[1] = '_'; // Separator

        // Now we get the opcode string
        snprintf(&output_line[2], 4, "%.3s", opcode_map[operation]);
        output_line[5] = ' '; // Space separator

        // Now we format the operand to represent the actual number (with decimal if needed) 
        if (operand % 100 == 0) {
            operand /= 100;
            snprintf(&output_line[6], 8, "%d\n", operand); // Reserve enough space for up to 6 digits (can only represent that many whole numbers), newline, and null terminator
        } else
        {
            snprintf(&output_line[6], 25, "%d.%02d\n", operand / 100, operand % 100);
        }
        fputs(output_line, output);
    }
    
    printf("Finished reading file, check out.\n");
    fclose(input);
    fclose(output);
    return 0;
}
