#ifdef CHANGED
#include "pageprovider.h"
#include "machine.h"


PageProvider::PageProvider(){
    memoryMap = new BitMap(NumPhysPages);
}

PageProvider::~PageProvider(){
    delete memoryMap;
    memoryMap = NULL;


}

unsigned int PageProvider::GetEmptyPage(){
    unsigned int freePage = memoryMap->Find();
    return (int) freePage;
}

void PageProvider::ReleasePage(unsigned int page){
    memoryMap->Clear(page);
}
unsigned int PageProvider::NumAvailPage(){
    return memoryMap->NumClear();
}

#endif