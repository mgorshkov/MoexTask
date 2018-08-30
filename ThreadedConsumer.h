#pragma once

#include "ThreadedActor.h"

template <typename DependentConsumer>
class ThreadedConsumer : public ThreadedActor
{
public:
    ThreadedConsumer(Synchronizer& aSynchronizer)
        : ThreadedActor(aSynchronizer)
    {
    }

protected:
    template <typename... Args>
    void Run(std::forward<Args>(args)...)
    {
        DependentConsumer dependentConsumer(mSynchronizer.mStopper);
        while (!mSynchronizer.IsStopped())
        {
            Mutex mutex;
            UniqueLock<Mutex> lock(mutex);
            mSynchronizer.Wait(mutex);
            if (!mSynchronizer.IsStopped())
                ProcessElement(dependentConsumer);
        }
    }

    void ProcessElement(IConsumer& aDependentConsumer)
    {
        auto element = mSynchronizer.GetQueueElement();
        if (element)
            aDependentConsumer.Consume(std::move(element));
    }
};

