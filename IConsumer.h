#pragma once

#include "Defines.h"

class IConsumer
{
public:
    virtual ~IConsumer() = default;
    virtual void Consume(DataPtr&& aData) = 0;
};
