#ifdef CHANGED
#include "machine.h"
#include "bitmap.h"

class PageProvider
{
private:
    BitMap memoryMap;
public:
    PageProvider(/* args */);
    ~PageProvider();

    unsigned int GetEmptyPage();
    void ReleasePage(unsigned int page);
    unsigned int NumAvailPage();
};

#endif //changed