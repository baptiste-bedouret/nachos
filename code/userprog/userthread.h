#ifdef CHANGED
#ifndef USERTHREAD_H
#define USERTHREAD_H

/*class Userthread{
    public:

    extern int do_ThreadCreate(int f, int arg);

    private:
    Thread *thread;

};*/

extern int do_ThreadCreate(int f, int arg);

static void StartUserThread(void *schmurtz);

extern void do_ThreadExit();

#endif // USERTHREAD_H
#endif // CHANGED
