I_INP //input new number in the register
I_ADD // Add given number to the register
I_SUB // subtract given number from the register
I_MUL // multiply given number from the register
I_DIV // divide given number from the register
I_MOD // modulo (give remainder) from the register

I_EQU // from given adress, check if number given is equal to that address
I_GRE // from given adress, check if number given is greater to that address
I_LES // from given adress, check if number given is less than that address
I_EGR // from given adress, check if number given is equal to or greater than that address
I_ELE // from given adress, check if number given is less than or equal to that address

M_INP // Input register to provided memory address
M_OUT // treats the first register as a memory address, from that address outputs data to second given register
M_ADD // from given address, add to register
M_SUB // from given address, subtract from register
M_MUL // from given address, multiply the register
M_DIV // from given address, divide the register

I_MOD // from given addres, module (give remainder) the register


I_JUM // skips x amt instructions



Example instruction:
I_INP UINT B 7
I_INP UINT A 0
I_MOD UINT A 2
I_EQU UINT A 1
I_JUM 3
#if the number is even divite it by 2#
M_OUT B A
I_MUL UINT A 3
I_ADD UINT A 1
#output next sequence number#
I_ADD UINT B 7
M_OUT B A
I_GRE UINT A 1
I_JUM -13
#calcualte number of elements in sequence#
I_DIV UINT B 7
M_INP UINT B


Instruction format:
2 digit op code
1 digit mode
1 digit number mode
1 digit target register
then a  7 digit number for operations, trating each digit differently depending on the number mode read

\# -> will denote comments \#

I am considering making a "eol" statement since some commands do not need the full information AND the default is a uint unless specified. I will try to do without though!

Goal: 
Based on Episode 7s's instruction set make:
1. "compiler" that reads an input file containing numbers and writes to an out file
that contains the appropriate ""Assembly code"" (see above)
    ? 1a. "Decompiler" that takes the ""Assembly code"" and writes the instuction format (might be fun)
2. An executer that takes the (Assembly code ? Instruction format) and executes the program (currently its just numbers)
3. Add comment ability. Decompiler will ignore these. lines 



