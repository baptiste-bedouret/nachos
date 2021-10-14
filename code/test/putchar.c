/**
 * @brief putChar displays one character at a time
 * @details in the function main we test the different behaviors of putChar.
 * @param. char (the character to print)
 * @return displays the character.
*/

#include "syscall.h"

int 
main(){
    //Testing putchar with normal character
    //Expected: PutChar to display the character 
    PutChar('a');

    //Testing putchar with '\n'
    //Expected 'b' to be in a new line
    PutChar('\n');
    PutChar('b');
    
    //Testing putchar with '\0'
    //Expected :'\0' will not be printed
    PutChar('\0');
    PutChar('d');

    Halt();
}