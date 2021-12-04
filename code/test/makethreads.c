#include "syscall.h"

void test_putchar(void *arg)
{
    char which = (char)arg;
    PutChar(which);
    ThreadExit();
}

volatile int i;

int main()
{
    PutChar('z');
    ThreadCreate(test_putchar, (void *)'a');
    ThreadCreate(test_putchar, (void *)'b');
    ThreadCreate(test_putchar, (void *)'c');
    for(i=0;i<10;i++){
        ThreadCreate(test_putchar, (void *)'c');
    }
    
    PutChar('z');
    ThreadExit();
}