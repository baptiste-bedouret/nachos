#ifdef CHANGED


#include "pageprovider.h"
#include <ctime>
#include <cstdlib>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "system.h"
PageProvider::PageProvider(int nbPages){
    memoryMap = new BitMap(nbPages);
}

PageProvider::~PageProvider(){
    delete memoryMap;
    memoryMap = NULL;


}

unsigned int PageProvider::GetEmptyPage(){
    int freePage = memoryMap->Find();
    char * addr = machine->mainMemory + (freePage * PageSize);
    memset(addr, 0,PageSize);
    return (unsigned int) freePage;
}

void PageProvider::ReleasePage(unsigned int page){
    memoryMap->Clear(page);
}
unsigned int PageProvider::NumAvailPage(){
    return (unsigned int) memoryMap->NumClear();
}

unsigned int PageProvider::GetRandomPage(){
    srand((unsigned)time(0));
    unsigned int randomPage = (rand() % memoryMap->NumClear()) ;

    while(memoryMap->Test(randomPage)){
        randomPage = (rand() % memoryMap->NumClear());
    }


    char * addr = machine->mainMemory + (randomPage * PageSize);
    memset(addr, 0,PageSize);
    return randomPage;
}

#endif
