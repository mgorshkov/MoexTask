#include "stdafx.h"

void Stopper::Stop()
{
	InterlockedExchange(&mDone, 1);
}

bool Stopper::IsStopped() const
{
	return mDone == 1;
}

