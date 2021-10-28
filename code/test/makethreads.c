#include "syscall.h"

void test_putchar(void *arg){
    char which = (char) arg;
    PutChar(which);

}

int 
main(){
    ThreadCreate(test_putchar, (void*) 'a')

    Halt();
}