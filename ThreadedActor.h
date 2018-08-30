#pragma once

#include "Synchronizer.h"

#include <thread>

class ThreadedActor
{
public:
    ThreadedActor(Synchronizer& aSynchronizer);

    virtual ~ThreadedActor();

    void Start();
    void Join();

protected:
    Synchronizer& mSynchronizer;

private:
    static void ThreadProc(ThreadedActor* aThis);

    bool mIsRunning;

    std::thread mThread;
};

