#include "ThreadedActor.h"

#include <iostream>

ThreadedActor::ThreadedActor(Synchronizer& aSynchronizer)
    : mSynchronizer(aSynchronizer)
    , mIsRunning(false)
{
}

ThreadedActor::~ThreadedActor()
{
    if (mIsRunning)
        std::cerr << "~ThreadedActor on running threads" << std::endl;
}

void ThreadedActor::Start()
{
    mThread = std::move(std::thread(ThreadProc, this));

    mIsRunning = true;
}

void ThreadedActor::Join()
{
#ifdef DEBUG_PRINT
    std::cout << "ThreadedActor::Join" << std::endl;
#endif

    if (!mIsRunning)
        return;
    if (mThread.joinable())
        mThread.join();
    mIsRunning = false;

#ifdef DEBUG_PRINT
    std::cout << "ThreadedActor::Join finished" << std::endl;
#endif
}

void ThreadedActor::ThreadProc(ThreadedActor* aThis)
{
    try
    {
        aThis->Run();
    }
    catch (const std::exception& e)
    {
        std::cerr << "Exception in ThreadedActor: " << e.what() << std::endl;
    }
}

