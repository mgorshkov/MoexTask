#include "Synchronizer.h"

Synchronizer::Synchronizer(IStopperPtr aStopper)
    : mStopper(aStopper)
{
}

void Synchronizer::EnqueueTask(TaskPtr&& aTask)
{
    {
        UniqueLock<Mutex> lk(mQueueMutex);
        mQueue.emplace(std::move(aTask));
    }
    mCondition.Broadcast();
}

TaskPtr Synchronizer::GetQueueElement()
{
    UniqueLock<Mutex> lk(mQueueMutex);
    if (mQueue.empty())
        return nullptr;
    auto element = std::move(mQueue.front());
    mQueue.pop();
    return std::move(element);
}

void Synchronizer::Wait(Mutex& aMutex)
{
    mCondition.Wait(aMutex);
}

void Synchronizer::Stop()
{
    mStopper->Stop();
    mCondition.Broadcast();
}

bool Synchronizer::IsStopped() const
{
    return mStopper->IsStopped();
}
