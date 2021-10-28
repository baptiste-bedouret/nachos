#ifdef CHANGED

#include "userthread.h"
#include "system.h"

extern int do_ThreadCreate(int f, int arg)
{
    Thread *newThread = new Thread("userthread");
    newThread->space = currentThread->space;
    newThread->Start(StartUserThread, arg);
    return 0;
}

static void StartUserThread(void *schmurtz)
{
    int i;

    for (i = 0; i < NumTotalRegs; i++)
        machine->WriteRegister(i, 0);

    // Initial program counter -- must be location of "Start"
    machine->WriteRegister(PCReg, USER_START_ADDRESS);

    // Need to also tell MIPS where next instruction is, because
    // of branch delay possibility
    machine->WriteRegister(NextPCReg, machine->ReadRegister(PCReg) + 4);

    // Set the stack register to the end of the address space, where we
    // allocated the stack; but subtract off a bit, to make sure we don't
    // accidentally reference off the end!
    machine->WriteRegister(StackReg, numPages * PageSize - 256);
    DEBUG('a', "Initializing stack register to 0x%x\n",
          numPages * PageSize - 256);

    machine->Run();
}

extern int do_ThreadExit(int f, int arg)
{
    currentThread->Finish;
}
#endif //changed