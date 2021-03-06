// exception.cc 
//      Entry point into the Nachos kernel from user programs.
//      There are two kinds of things that can cause control to
//      transfer back to here from user code:
//
//      syscall -- The user code explicitly requests to call a procedure
//      in the Nachos kernel.  Right now, the only function we support is
//      "Halt".
//
//      exceptions -- The user code does something that the CPU can't handle.
//      For instance, accessing memory that doesn't exist, arithmetic errors,
//      etc.  
//
//      Interrupts (which can also cause control to transfer from user
//      code into the Nachos kernel) are handled elsewhere.
//
// For now, this only handles the Halt() system call.
// Everything else core dumps.
//
// Copyright (c) 1992-1993 The Regents of the University of California.
// All rights reserved.  See copyright.h for copyright notice and limitation 
// of liability and disclaimer of warranty provisions.

#include "copyright.h"
#include "system.h"
#include "syscall.h"

//----------------------------------------------------------------------
// UpdatePC : Increments the Program Counter register in order to resume
// the user program immediately after the "syscall" instruction.
//----------------------------------------------------------------------
static void
UpdatePC ()
{
    int pc = machine->ReadRegister (PCReg);
    machine->WriteRegister (PrevPCReg, pc);
    pc = machine->ReadRegister (NextPCReg);
    machine->WriteRegister (PCReg, pc);
    pc += 4;
    machine->WriteRegister (NextPCReg, pc);
}


//----------------------------------------------------------------------
// ExceptionHandler
//      Entry point into the Nachos kernel.  Called when a user program
//      is executing, and either does a syscall, or generates an addressing
//      or arithmetic exception.
//
//      For system calls, the following is the calling convention:
//
//      system call code -- r2
//              arg1 -- r4
//              arg2 -- r5
//              arg3 -- r6
//              arg4 -- r7
//
//      The result of the system call, if any, must be put back into r2. 
//
// And don't forget to increment the pc before returning. (Or else you'll
// loop making the same system call forever!
//
//      "which" is the kind of exception.  The list of possible exceptions 
//      are in machine.h.
//----------------------------------------------------------------------

char buffer[MAX_STRING_SIZE];

/**
 * @brief copy the content of the address (from) to the pointer (to).
 * 
 * @param from : the memory address of the string 
 * @param to : the pointer where the string will be stored
 * @param size : the size of the string to copy limited by the size of the buffer
 * @return int : the size of the string stored in (to)
 */
static int copyStringFromMachine(int from, char *to, unsigned size){
    
    int i = 0;
    for(; i < size; i++){
        int chToCopy;
        char val = machine->ReadMem(from+i,1,&chToCopy); //(address,size=1,);
        char ch = (char)chToCopy; 
        to[i] = ch;

        if((char)chToCopy == '\0'){
            break;
        }
    }
    if(to[i] == '\0'){
        return i;
    }else{
        to[i] = '\0';
        return i+1;
    } 

}

/**
 * @brief Stores a string at a specific address, we used the method (WriteMem) to store the string
 * 
 * @param address : the address to store the string in.
 * @param size : the size of the string limited by the buffer size.
 * @param values : the string to store in the address.
 * @return int : the address of the stored string
 */
static int copyStringToMachine(int address, int size, char *values){
	int index = 0;
	bool resOfWriteMem = true;
	while(index < size && values[index] != '\0' && resOfWriteMem && values[index] != '\n'){
		resOfWriteMem = machine->WriteMem(address + index,1,values[index]);
		index++;
	}
	return address;
}


void
ExceptionHandler (ExceptionType which)
{
    int type = machine->ReadRegister (2);
    int address = machine->registers[BadVAddrReg];

    switch (which)
      {
	case SyscallException:
          {
	    switch (type)
	      {
		#ifdef CHANGED
		case SC_PutChar:
		{
			DEBUG('s',"PutChar\n ");
			//using PutChar to write down the content of the register 4 
			consoledriver->PutChar(machine->ReadRegister(4));
		    break;
		}

		case SC_PutString:
		{
			
			DEBUG('s',"PutString\n ");
			//Using copyStringFromMachine to copy the strinng from reg(4) to the buffer
			copyStringFromMachine(machine->ReadRegister(4),buffer,MAX_STRING_SIZE);
			//Using PutString to write the content of the buffer
			consoledriver->PutString(buffer);
			break;

		}

		case SC_GetChar:
		{
			DEBUG('s',"GetChar\n ");
			//Reading the character using GetChar
			int ch = consoledriver->GetChar();
			//Saving the character in the reg(2)
			machine->WriteRegister(2,ch);
			break;
		}

		case SC_GetString:
		{
			
			DEBUG('s',"GetString\n ");
			//Reading the string and puting it in the buffer
			consoledriver->GetString(buffer, MAX_STRING_SIZE);
			//Copying the string from the buffer to the reg(4)
			copyStringToMachine(machine->ReadRegister(4),strlen(buffer),buffer); 
			break;
		}
		
		#endif //changed	

		case SC_Halt:
		  {
		    DEBUG ('s', "Shutdown, initiated by user program.\n");
		    interrupt->Powerdown ();
		    break;
		  }
		
		default:
		  {
		    printf("Unimplemented system call %d\n", type);
		    ASSERT(FALSE);
		  }
	      }

	    // Do not forget to increment the pc before returning!
	    UpdatePC ();
	    break;
	  }

	case PageFaultException:
	  if (!address) {
	    printf("NULL dereference at PC %x!\n", machine->registers[PCReg]);
	    ASSERT (FALSE);
	  } else {
	    printf ("Page Fault at address %x at PC %x\n", address, machine->registers[PCReg]);
	    ASSERT (FALSE);	// For now
	  }
	  break;

	case ReadOnlyException:
	  printf ("Read-Only at address %x at PC %x\n", address, machine->registers[PCReg]);
	  ASSERT (FALSE);	// For now
	  break;

	case BusErrorException:
	  printf ("Invalid physical address at address %x at PC %x\n", address, machine->registers[PCReg]);
	  ASSERT (FALSE);	// For now
	  break;

	case AddressErrorException:
	  printf ("Invalid address %x at PC %x\n", address, machine->registers[PCReg]);
	  ASSERT (FALSE);	// For now
	  break;

	case OverflowException:
	  printf ("Overflow at PC %x\n", machine->registers[PCReg]);
	  ASSERT (FALSE);	// For now
	  break;

	case IllegalInstrException:
	  printf ("Illegal instruction at PC %x\n", machine->registers[PCReg]);
	  ASSERT (FALSE);	// For now
	  break;

	default:
	  printf ("Unexpected user mode exception %d %d %x at PC %x\n", which, type, address, machine->registers[PCReg]);
	  ASSERT (FALSE);
	  break;
      }
}


