#pragma once

#include "Defines.h"

class IProducer
{
public:
    virtual ~IProducer() = default;
    virtual DataPtr Produce() = 0;

    virtual void Stop() {}
};

