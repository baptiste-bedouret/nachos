#include "syscall.h"

int 
main(){
    char s[MAX_STRING_SIZE];
    GetString(s,MAX_STRING_SIZE);
    PutString(s);
    Halt();
}