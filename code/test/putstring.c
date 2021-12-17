/**
 * @brief Testing the method putstring
 * @details The method getstring takes a pointer to a string and prints that string, if the string is longer then MAX_STRING_SIZE
 * put string will only display a part of it
 * @param. The string
 * @return void it only displays the string
*/


#include "syscall.h"

int 
main(){
    
    //Testint putstring with a string shorter then (MAX_STRING_SIZE=20)
    //Expected: putstring to display the whole string
    char *s  = "234567890123456789"; 
    PutString(s);
    Halt();
    
    
    /*
    //Testint putstring with a string longer then (MAX_STRING_SIZE=20)
    //Expected: putstring to print the first part of the string but not "this should not appear"
    char *s  = "01234567890123456789 this should not appear"; 
    PutString(s);
    Halt();
    */
    
    //Testint putstring when encountring (\n)
    //Expected: to start a new line and continue printing
    /*
    char *s  = "012345\n789"; 
    PutString(s);
    Halt();
    */
    

    //Testint putstring when encountring (\0)
    //Expected: to stop printing
    /*
    char *s  = "0123\0 this should not appear"; 
    PutString(s);
    Halt();
    */
    
    
}