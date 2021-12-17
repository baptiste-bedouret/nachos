#include "syscall.h"

volatile int i;
volatile int N = 20;


int main()
{
    PutChar('z');
    
    for(i=0;i<N;i++){
        ForkExec("../test/makethreads");
    }

 
    PutChar('z');
    Halt();
}