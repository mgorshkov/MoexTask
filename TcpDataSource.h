#pragma once

#include "Defines.h"
#include "IProducer.h"
#include "IReader.h"
#include "IStopper.h"
#include "TsvParser.h"
#include "TcpServer.h"

#include <sstream>
#include <thread>
#include <atomic>
#include <condition_variable>
#include <mutex>

class TcpDataSource : public IProducer, public IReader
{
public:
    TcpDataSource(IStopperPtr aStopper, int mPort);

    DataPtr Produce() const override;

private:
    static void ThreadProc(TcpDataSource* aContext);

    void Read(const char* aData, std::size_t aSize) override;

    IStopperPtr mStopper;
    int mPort;
    TsvParser mParser;

    std::stringstream mStream;
    mutable std::mutex mStreamMutex;
    std::condition_variable mCondition;
    std::atomic_bool mDone{false};
    std::atomic_bool mNotified{false};

    std::thread mThread;
};