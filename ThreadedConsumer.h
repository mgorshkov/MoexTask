#pragma once

#include "IConsumer.h"
#include "ThreadedActor.h"

template <typename DependentConsumer>
class ThreadedConsumer : public ThreadedActor
{
public:
    ThreadedConsumer(Synchronizer& aSynchronizer)
        : ThreadedActor(aSynchronizer)
        , mDependentConsumer(aSynchronizer)
    {
    }

    DependentConsumer* GetConsumer()
    {
        return &mDependentConsumer;
    }

protected:
    void Run() override
    {
        while (!mSynchronizer.IsStopped())
        {
            std::mutex mutex;
            std::unique_lock<std::mutex> lock(mutex);
            mSynchronizer.Wait(lock);
            if (!mSynchronizer.IsStopped())
                ProcessElement();
        }
    }

    void ProcessElement()
    {
        auto element = mSynchronizer.GetQueueElement();
        if (element)
            mDependentConsumer.Consume(std::move(element));
    }

private:
    DependentConsumer mDependentConsumer;
};

