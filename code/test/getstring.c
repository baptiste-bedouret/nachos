/**
 * @brief Reads a string shorter or equal to (MAX_STRING_SIZE=20) .
 * @details GetString asks of the user to enter a string it reads the string and saves it in the register of the machine to be used later on by 
 * other functions like PutString.
 * @param.
 * @return String.
 */
#include "syscall.h"

int 
main(){
    char s[MAX_STRING_SIZE];
    GetString(s,MAX_STRING_SIZE);
    PutString(s);
    Halt();
}