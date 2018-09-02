#pragma once

#include <chrono>

#include "ThreadedActor.h"
#include "Synchronizer.h"

template <typename DependentProducer>
class ThreadedProducer : public ThreadedActor
{
public:
    template <typename... Args>
    ThreadedProducer(Synchronizer& aSynchronizer, Args&&... args)
        : ThreadedActor(aSynchronizer)
        , mDependentProducer(mSynchronizer.mStopper, std::forward<Args>(args)...)
    {
    }
    
protected:
    void Run() override
    {
        while (!mSynchronizer.IsStopped())
        {
            DataPtr data = mDependentProducer.Produce();
            if (!data)
                break;

            mSynchronizer.EnqueueData(std::move(data));

            std::this_thread::sleep_for(std::chrono::milliseconds(10));
        }
    }

private:
    DependentProducer mDependentProducer;
};

