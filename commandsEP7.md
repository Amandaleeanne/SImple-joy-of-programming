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

I_EQ // from given adress, check if number given is equal to that address
I_GR // from given adress, check if number given is greater to that address


Example instruxtion:
I_INP 8
I_MUL 11
M_INP 18
I_INP 24
I_MUL 38
M_ADD 18
M_INP 6


Instruction format:
2 digit op code
1 digit mode
1 digit number mode
1 digit target register
then a  7 digit number for operations, trating each digit differently depending on the number mode read



Goal: 
Based on Episode 3's instruction set make:
1. "compiler" that reads an input file containing numbers and writes to an out file
that contains the appropriate ""Assembly code"" (see above)
    ? 1a. "Decompiler" that takes the ""Assembly code"" and writes the instuction format (might be fun)
2. An executer that takes the (Assembly code ? Instruction format) and executes the program (currently its just numbers)



