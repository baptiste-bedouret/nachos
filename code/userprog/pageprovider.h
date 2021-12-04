#ifndef PAGEPROVIDER_H
#define PAGEPROVIDER_H

#include "bitmap.h"

#ifdef CHANGED
class PageProvider
{
private:
    BitMap *memoryMap;
public:
    PageProvider(int nbPages);
    ~PageProvider();

    unsigned int GetEmptyPage();
    void ReleasePage(unsigned int page);
    unsigned int NumAvailPage();
    unsigned int GetRandomPage();
};

#endif //changed

#endif