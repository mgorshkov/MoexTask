#pragma once

#include <atomic>

#include "IStopper.h"

class Stopper : public IStopper
{
public:
    void Stop() override;

    bool IsStopped() const override;

private:
    std::atomic_bool mDone{false};
};

