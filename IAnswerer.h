#pragma once

#include "Defines.h"

class IAnswerer
{
public:
    virtual ~IAnswerer() = default;

    virtual Statistics Answer(const std::string& aEvent) = 0;
};
