#pragma once

#include <memory>

class IStopper
{
public:
	virtual ~IStopper() = default;

	virtual void Stop() = 0;

	virtual bool IsStopped() const = 0;
};

using IStopperPtr = std::shared_ptr<IStopper>;
