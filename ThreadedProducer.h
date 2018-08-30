#pragma once

#include <chrono>

#include "ThreadedActor.h"
#include "Synchronizer.h"

template <typename DependentProducer>
class ThreadedProducer : public ThreadedActor
{
public:
    ThreadedProducer(Synchronizer& aSynchronizer)
        : ThreadedActor(aSynchronizer)
    {
    }
    
protected:
    template <typename... Args>
    void Run(Args&&... args)
    {
        DependentProducer dependentProducer(mSynchronizer.mStopper, std::forward<Args>(args)...);
        while (!mSynchronizer.IsStopped())
        {
            DataPtr data = dependentProducer.Produce();
            if (!data)
                break;

            mSynchronizer.EnqueueData(std::move(data));

            std::this_thread::sleep_for(std::chrono::milliseconds(10));
        }
    }
};

