#pragma once

#include "Defines.h"
#include "IStopper.h"
#include <condition_variable>
#include <mutex>

struct Synchronizer
{
public:
    explicit Synchronizer(IStopperPtr aStopper);

    void EnqueueData(DataPtr&& aData);
    DataPtr GetQueueElement();

    void Wait(std::mutex& aMutex);

    void Stop();

    bool IsStopped() const;

    DataQueue mQueue;
    std::condition_variable mCondition;
    std::mutex mQueueMutex;
    std::shared_ptr<IStopper> mStopper;
};
