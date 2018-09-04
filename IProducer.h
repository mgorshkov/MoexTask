#pragma once

#include "Defines.h"

class IProducer
{
public:
    virtual ~IProducer() = default;
    virtual DataPtr Produce() = 0;

    virtual void Stop() {
#ifdef DEBUG_PRINT
    std::cout << "IProducer::Stop" << std::endl;
#endif

    }
};

