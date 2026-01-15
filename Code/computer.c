
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

int memory[1000] = {0}; //Memory model
__int32 RAM_REG = 0; //for 6digits

/**
 * Turns the encoded instructions (00000004) to do something with it
 */
int read_instructions(FILE *input, int to_terminal)
{
    //read instructions from given file
    int operation;
    int mode;
    int operand;
    int code = 0; //for return codes
    int instructionCounter = 0;
    while (fscanf(input, "%2d %1d %6d", &operation, &mode, &operand) != 3) {
        
        // Process the read values
        printf("Operation: %d, Mode: %d, Operand: %d\n", operation, mode, operand);

        if (operation < 0 || operation > 5) {
            fprintf(stderr, "Error: operation code %d out of bounds (0-5). Skipping line.\n", operation);
            code -= 1;
            continue;
        }

        if (mode < 0 || mode > 1) {
            fprintf(stderr, "Error: mode %d out of bounds (0-1). Skipping line.\n", mode);
            code -= 2;
            continue;
        }
        //preform control flow to execute instructions
        if (mode == 0) 
        { // Immediate mode
            switch (operation) {
                case 0: // INP
                    RAM_REG = operand;
                    break;
                case 2: // ADD
                    RAM_REG += operand;
                    break;
                case 3: // SUB
                    RAM_REG -= operand;
                    break;
                case 4: // MUL
                    RAM_REG *= operand;
                    break;
                case 5: // DIV
                    if (operand == 0) {
                        fprintf(stderr, "Error: Division by zero at line %d \n", instructionCounter);
                        exit(EXIT_FAILURE);
                    }
                RAM_REG /= operand;
                    break;
                default:
                    fprintf(stderr, "Error: Invalid operation code %d in immediate mode at line %d.\n", operation, instructionCounter);
                    return -1;
            }
        } else{
            switch (operation) {
                    case 0: // INP
                        memory[operation] = RAM_REG;
                        break;
                    case 2: // ADD
                        RAM_REG += memory[operand];
                        break;
                    case 3: // SUB
                        RAM_REG -= memory[operand];
                        break;
                    case 4: // MUL
                        RAM_REG *= memory[operand];
                        break;
                    case 5: // DIV
                        if (memory[operand] == 0) {
                            fprintf(stderr, "Error: Division by zero on line %d\n", instructionCounter);
                            exit(EXIT_FAILURE);
                        }
                    RAM_REG /= memory[operand];
                        break;
                    default:
                        fprintf(stderr, "Error: Invalid operation code %d in immediate mode.\n", operation);
                        return -1;
                }
        }
    instructionCounter++;
}
    

    return 0;
}