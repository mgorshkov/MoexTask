#pragma once

#include <condition_variable>
#include <mutex>

#include "Defines.h"
#include "IStopper.h"

struct Synchronizer
{
public:
    explicit Synchronizer(IStopperPtr aStopper);

    void EnqueueData(DataPtr&& aData);
    DataPtr GetQueueElement();

    void Stop();

    bool IsStopped() const;

    DataQueue mQueue;
    std::condition_variable mCondition;
    std::mutex mQueueMutex;
    IStopperPtr mStopper;
};
