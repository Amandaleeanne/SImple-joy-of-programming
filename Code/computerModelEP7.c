#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int disassemble(FILE *input, FILE *output);
int assemble(FILE *input, FILE *output);

typedef enum {
    INP = 0,
    OUT = 1,
    ADD = 2,
    SUB = 3,
    MUL = 4,
    DIV = 5
} Opcode;

char opcode_map[6][4] = {
    "INP",
    "OUT",
    "ADD",
    "SUB",
    "MUL",
    "DIV",
};

int memory[1000] = {0};

int operation;
int mode;
int operand;

int main(int argc, char const *argv[])
{
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <file> <out> -r|NULL\n", argv[0]);
        return 1;
    } 

    FILE *input = fopen(argv[1], "r");
    FILE *output = fopen(argv[2], "w");
    if (input == NULL || output == NULL) {
        perror("Error opening file");
        return 1;
    }
    int return_code;
    int to_run = (strcmp(argv[3], "-r") == 0) ? 0 : 1;

    //test weather given input is numbers or ""Assembly""
    char test_char;
    fscanf(input, "%c", &test_char);
    ungetc(test_char, input); //put it back because we are seeing what the code start with
    if( (test_char >= '0' && test_char <= '9')) //if it is a number we are assembling into readable code
    {
        return_code = assemble(input, output);
    }else
    {
        return_code = disassemble(input, output);
    }


    if (return_code != 0) {
        fprintf(stderr, "Error during compiler processing\n Return code: %d\n", return_code);
        fclose(input);
        fclose(output);
        return 1;
    }

    if (to_run)
    {
        printf("Running code...\n");
        rewind(output);
    }

    fclose(input);
    fclose(output);
    return 0;
}

/**
 * turns assembly code into its correct number format
 */
int disassemble(FILE *input, FILE *output) {
    char mode_char;
    char opcode_str[4];
    int  operand_int;
    int  decimal_part = 0;
    char line[32];
    int code = 0;
    while (fgets(line, 32, input) != NULL) //file scan to consume the line
    {
        decimal_part = 0; //reset
        // Parse the line (one with decimal and one without)
        if (sscanf(line, "%c_%3s %d.%d", &mode_char, opcode_str, &operand_int, &decimal_part) < 3
        || sscanf(line, "%c_%3s %d", &mode_char, opcode_str, &operand_int) < 3) {
                fprintf(stderr, "Error: invalid line format '%s'. Skipping line.\n", line);
                code = 1;
                continue;
            }

        operation = -1;
        mode = -1;
        operand = 0;
        
        // Determine mode
        if (mode_char == 'I') {
            mode = 0; // Immediate mode
        } else if (mode_char == 'M') {
            mode = 1; // Memory mode
        } else {
            fprintf(stderr, "Error: invalid mode character '%c'. Skipping line.\n", mode_char);
            code += 2;
            continue;
        }

        // Determine operation code
        for (int i = 0; i < 6; i++) {
            if (strcmp(opcode_str, opcode_map[i]) == 0) {
                operation = i;
                break;
            }
        }
        if (operation == -1) {
            fprintf(stderr, "Error: invalid opcode '%s'. Skipping line.\n", opcode_str);
            code += 4;
            continue;
        }

        // Calculate operand
        fprintf(output, "%02d%01d%06d", operation, mode, operand_int *100+ decimal_part);        
        fflush(output); // Ensure data is written immediately (testing)
    }
    printf("Finished reading file, check out.\n");
    return code;
}

/**
 * turns numbers format into an out with "assembly" code
 */
int assemble(FILE *input, FILE *output) {

    char output_line[32]; //max example: I_INP 8000.00\0
    int code = 0;
    while (fscanf(input, "%2d %1d %6d", &operation, &mode, &operand) == 3)
    {
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

        //first we want to check the mode to see if the read value is immediate or memory
        if (mode == 1) {output_line[0] = 'M'; } // Memory mode
            output_line[0] = 'I'; // Immediate mode (default)

        output_line[1] = '_'; // Separator

        // Now we get the opcode string
        snprintf(&output_line[2], 4, "%.3s", opcode_map[operation]);
        output_line[5] = ' '; // Space separator

        // Now we format the operand to represent the actual number (with decimal if needed) 
        if (operand % 100 == 0) {
            operand /= 100; //get rid of "float"
            snprintf(&output_line[6], 8, "%d\n", operand); // Reserve enough space for up to 6 digits (can only represent that many whole numbers), newline, and null terminator
        } else
        {
            snprintf(&output_line[6], 25, "%d.%02d\n", operand / 100, operand % 100);
        }
        fputs(output_line, output);
    }
    
    printf("Finished reading file, check out.\n");
    return code;
}


//does something with the instructions....though i might wanna lookup seperate C hearder files and all that
//because the computer model itself should not be a compiler.
int read_instrcutions(FILE *input, int to_terminal)
{
    //read instructions from given file
        //preform control flow to execute instructions
    

    return 0;
}