#include "Synchronizer.h"

Synchronizer::Synchronizer(IStopperPtr aStopper)
    : mStopper(aStopper)
{
}

void Synchronizer::EnqueueData(DataPtr&& aData)
{
    {
        std::unique_lock<std::mutex> lk(mQueueMutex);
        mQueue.emplace(std::move(aData));
    }
    mCondition.notify_all();
}

DataPtr Synchronizer::GetQueueElement()
{
    std::unique_lock<std::mutex> lk(mQueueMutex);
    if (mQueue.empty())
        return nullptr;
    auto element = std::move(mQueue.front());
    mQueue.pop();
    return std::move(element);
}

void Synchronizer::Wait(std::unique_lock<std::mutex>& aLock)
{
    mCondition.wait(aLock);
}

void Synchronizer::Stop()
{
    mStopper->Stop();
    mCondition.notify_all();
}

bool Synchronizer::IsStopped() const
{
    return mStopper->IsStopped();
}
