#ifdef CHANGED

#include "userproc.h"
#include "system.h"


static Thread *threadPrincipal;

int do_ForkExec(const char *s)
{

    threadPrincipal = currentThread;
    OpenFile *executable = fileSystem->Open(s);

    AddrSpace *newAdd = new  AddrSpace(executable);
    Thread *newThread = new Thread("userthread");

    newThread->space = newAdd;
    StartUserProc(newThread);

    return 0;

}

static void StartUserProc(Thread *newThread)
{
    newThread->space->InitRegisters();
    machine->Run();
}

#endif