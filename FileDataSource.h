#pragma once

#include <fstream>

class FileDataSource : public IProducer
{
public:
    FileDataSource(IStopperPtr aStopper, const std::string& aFileName);

    DataPtr Produce() override const;

private:
    std::ifstream aStream;
};


TaskPtr Producer::Produce() const
{
    auto request = Original::GetRequest(mStopper);
    return std::make_unique<Task>(request);
}
