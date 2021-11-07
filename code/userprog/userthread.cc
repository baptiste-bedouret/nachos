#ifdef CHANGED

#include "userthread.h"
#include "system.h"

typedef struct
{
    int f;
    int arg;
} MyFunction;

extern int do_ThreadCreate(int f, int arg)
{
    MyFunction *function = (MyFunction *)malloc(sizeof(MyFunction));
    function->f = f;
    function->arg = arg;

    Thread *newThread = new Thread("userthread");
    newThread->space = currentThread->space;
    newThread->Start(StartUserThread, function);

    currentThread->Yield();
    return 0;
}

static void StartUserThread(void *schmurtz)
{
    MyFunction *function = (MyFunction *)schmurtz;
    int i;

    for (i = 0; i < NumTotalRegs; i++)
        machine->WriteRegister(i, 0);

    // Initial program counter -- must be location of "Start"
    machine->WriteRegister(PCReg, function->f);

    // Need to also tell MIPS where next instruction is, because
    // of branch delay possibility
    machine->WriteRegister(NextPCReg, machine->ReadRegister(PCReg) + 4);

    machine->WriteRegister(4, function->arg);

    // Set the stack register to the end of the address space, where we
    // allocated the stack; but subtract off a bit, to make sure we don't
    // accidentally reference off the end!
    machine->WriteRegister(StackReg, currentThread->space->AllocateUserStack() - 256 - 16);
    DEBUG('a', "Initializing stack register to 0x%x\n",
          currentThread->space->AllocateUserStack() - 256 - 16);

    machine->DumpMem("threads.svg");

    machine->Run();
}

extern void do_ThreadExit()
{
    currentThread->Finish();
    free(currentThread->space);
}
#endif //changed