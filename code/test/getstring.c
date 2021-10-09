#include "syscall.h"

int 
main(){
    char *s;
    GetString(s,5);
    PutString(s);
    Halt();
}