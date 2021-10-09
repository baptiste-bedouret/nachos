#include "syscall.h"

int 
main(){
    char *s  = "hhazertyufffffffffffffffffffffffffffend\0hend"; 
    PutString(s);
    Halt();
}