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
/**
 * @brief Uses console->TX to write one character (ch)
 * 
 * @param ch : the character to be written.
 */
void ConsoleDriver::PutChar(int ch){
    char chToPut = (char)(ch);
    console->TX (chToPut);
    writeDone->P ();
}

/**
 * @brief Reads one character using console->RX()
 * 
 * @return int : the character read by the method
 */
int ConsoleDriver::GetChar(){
    readAvail->P ();
    char ch = console->RX ();

    return (int)(ch);
}
/**
 * @brief Writes a string of characters by calling PutChar multiple times 
 * 
 * @param s : the string to be written.
 */
void ConsoleDriver::PutString(const char s[]){
   int i =0;
   while(s[i] !='\0'){
       PutChar(s[i++]);
   } 
}

/**
 * @brief Reads from input a string of characters and stores it in the pointer (s)
 * 
 * @param s : pointer to a string 
 * @param n : the size of the string to read
 */
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