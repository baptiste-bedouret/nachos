#ifdef CHANGED

#include "userproc.h"
#include "system.h"


static Thread *threadPrincipal;
static Thread *newThread;

static unsigned nbProc = 0;
static Semaphore *semCounter = new Semaphore("thread counter", 1);


static void StartUserProc(void *schmurtz)
{
    AddrSpace *space = (AddrSpace *) schmurtz;
    space->InitRegisters();
    space->RestoreState ();
    machine->DumpMem ("memory.svg");
    machine->Run();
    ASSERT (FALSE);
}

int do_ForkExec(const char *s)
{

    threadPrincipal = currentThread;
    OpenFile *executable = fileSystem->Open(s);

    AddrSpace *newAdd;
    if (executable == NULL)
    {
	  SetColor (stdout, ColorRed);
	  SetBold (stdout);
	  printf ("Unable to open file %s\n", s);
	  ClearColor (stdout);
	  return -1;
    }

    newAdd = new AddrSpace(executable);
    newThread = new Thread("userthread");

    newThread->space = newAdd;
    delete executable;


    semCounter->P();
    nbProc++;
    semCounter->V();

    newThread->Start(StartUserProc, newAdd);

    return 0;

}



extern void do_ForkExit(){

    semCounter->P();
    if(nbProc == 0){
        semCounter->V();
        interrupt->Powerdown ();
    }else{
        nbProc--;
        semCounter->V();
        delete currentThread->space;
        currentThread->Finish();
    }
}


#endif