#pragma once

template <typename DependentProducer>
class ThreadedProducer : public ThreadedActor
{
public:
    template <typename... Args>
    ThreadedProducer(Args&&... args)
        : ThreadedActor(std::forward<Args>(args)...)
    {
    }
    
protected:
    void Run() override
    {
        DependentProducer dependentProducer(mSynchronizer.mStopper);
        while (!mSynchronizer.IsStopped())
        {
            DataPtr data = dependentProducer.Produce();
            if (!data)
                break;

            mSynchronizer.EnqueueData(std::move(data));

            Sleep(10);
        }
    }
};

