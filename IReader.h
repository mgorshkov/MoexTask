#pragma once

class IReader
{
public:
    virtual ~IReader() = default;

    virtual void Read(const char* buf, std::size_t size) = 0;
};

using IReaderPtr = IReader*;
