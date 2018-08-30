#include "Stopper.h"

void Stopper::Stop()
{
    mDone = true;
}

bool Stopper::IsStopped() const
{
    return mDone.load();
}

