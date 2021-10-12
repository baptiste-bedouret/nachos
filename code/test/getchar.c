/**
 * @brief reads one character given by the user.
 * @details In the function main the method GetChar reads one character then we use the method PutChar displays that character,
 * if the method GetChar was given more then one character it will only reads the first one
 * @param.
 * @return char (the character).
*/
#include "syscall.h"

int 
main(){
    char s  = GetChar(); 
    PutChar(s);
    Halt();
}