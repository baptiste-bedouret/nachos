#ifdef CHANGED

#include "userthread.h"

extern int do_ThreadCreate(int f, int arg){
    Thread *newThread= new Thread("userthread");
    newThread->space = currentThread->space + 256;
    return 0;
}
#endif //changed