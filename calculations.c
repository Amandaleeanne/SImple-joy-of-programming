
/* Reference:
I_INP //input new number in the register
I_ADD // Add given number to the register
I_SUB // subtract given number from the register
I_MUL // multiply given number from the register
I_DIV // divide given number from the register

M_INP // Input register to provided memory address
M_ADD // from given address, add to register
M_SUB // from given address, subtract from register
M_MUL // from given address, multiply the register
M_DIV // from given address, divide the register
*/

#include <stdio.h>
#include <stdlib.h>

typedef enum {
    A, // General pourpose 
    B // Memory adresses
} Registers;

static int memory[1000] = {0}; // Simple memory model

int read_instruction(FILE *input, Registers reg)
{
    int operation;
    int mode;
    int operand;
    if (fscanf(input, "%2d %1d %6d", &operation, &mode, &operand) != 3) {
        fprintf(stderr, "Error reading instruction from file.\n");
        return -1; // Indicate error
    }

    if (mode == 0) { // Immediate mode
        switch (operation) {
            case 0: // INP
                int value;
                printf("Enter a number: ");
                scanf("%d", &value);
                return value;
            case 2: // ADD
                return reg + operand;
            case 3: // SUB
                return reg - operand;
            case 4: // MUL
                return reg * operand;
            case 5: // DIV
                if (operand == 0) {
                    fprintf(stderr, "Error: Division by zero.\n");
                    exit(EXIT_FAILURE);
                }
                return reg / operand;
            default:
                fprintf(stderr, "Error: Invalid operation code %d in immediate mode.\n", operation);
                return -1;
        }
    } else if (mode == 1) { // Memory mode

        switch (operation) {
            case 0: // INP
                int value;
                printf("Enter a number to store at address %d: ", operand);
                scanf("%d", &value);
                memory[operand] = value;
                return 0; // No value to return
            case 2: // ADD
                return reg + memory[operand];
            case 3: // SUB
                return reg - memory[operand];
            case 4: // MUL
                return reg * memory[operand];
            case 5: // DIV
                if (memory[operand] == 0) {
                    fprintf(stderr, "Error: Division by zero.\n");
                    exit(EXIT_FAILURE);
                }
                return reg / memory[operand];
            default:
                fprintf(stderr, "Error: Invalid operation code %d in memory mode.\n", operation);
                return -1;
        }
    } else {
        fprintf(stderr, "Error: Invalid mode %d.\n", mode);
        return -1;
    }
    return 0;
}
