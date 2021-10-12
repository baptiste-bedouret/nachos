#ifdef CHANGED

#include "copyright.h"
#include "system.h"
#include "consoledriver.h"
#include "synch.h"

static Semaphore *readAvail;
static Semaphore *writeDone;
static void ReadAvailHandler(void *arg) { (void) arg; readAvail->V(); }
static void WriteDoneHandler(void *arg) { (void) arg; writeDone->V(); }

ConsoleDriver::ConsoleDriver(const char *in, const char *out)
{
    readAvail = new Semaphore("read avail", 0);
    writeDone = new Semaphore("write done", 0);
    console = new Console (in, out, ReadAvailHandler, WriteDoneHandler, NULL);
}
ConsoleDriver::~ConsoleDriver()
{
    delete console;
    delete writeDone;
    delete readAvail;
}

void ConsoleDriver::PutChar(int ch){
    char chToPut = (char)(ch);
    console->TX (chToPut);
    writeDone->P ();
}

int ConsoleDriver::GetChar(){
    readAvail->P ();
    char ch = console->RX ();

    return (int)(ch);
}

void ConsoleDriver::PutString(const char s[]){
    /*
    for(int i =0; i < sizeof(s); i++){
        char chToPut = s[i];
        PutChar((int) chToPut);
    }
    */
   int i =0;
   while(s[i] !='\0'){
       PutChar(s[i++]);
   } 

    
}
void ConsoleDriver::GetString(char *s, int n){
   int ch = GetChar();
   int index = 0;
   while(ch != '\n' && index < n){
       s[index] = (char)ch;
       ch = GetChar();
       index++;
   }
   s[index] = '\0';
}
#endif // CHANGED