#include "syscall.h"

void test_putchar(void *arg)
{
    char which = (char)arg;
    PutChar(which);
    ThreadExit();
}

volatile int i;
volatile int N = 20;


int main()
{
    PutChar('z');
    ThreadCreate(test_putchar, (void *)'a');
    ThreadCreate(test_putchar, (void *)'b');
    for(i=0;i<N;i++){
        ThreadCreate(test_putchar, (void *)'c');
    }
    
    PutChar('z');
    Halt();
}