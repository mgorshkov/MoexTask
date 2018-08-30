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
    if (!mIsRunning)
        return;
    if (mThread.joinable())
        mThread.join();
    mIsRunning = false;
}

void ThreadedActor::ThreadProc(ThreadedActor* aThis)
{
    try
    {
        aThis->Run();
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }
}

