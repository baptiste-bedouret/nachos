#include "syscall.h"

int 
main(){
    char s  = GetChar(); 
    PutChar(s);
    Halt();
}