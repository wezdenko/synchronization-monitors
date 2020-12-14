#pragma once
#include "monitor.h"
#include "Buffer.hpp"

class BufferMonitor : public Monitor
{
private:
    Buffer buffer;
    Condition putEvenCond, putOddCond, getEvenCond, getOddCond;

public:
    BufferMonitor();

    void putOdd(int value);
    void putEven(int value);

    int getOdd();
    int getEven();

private:
    bool canPutEven() const;
    bool canGetEven() const;

    bool canPutOdd() const;
    bool canGetOdd() const;

};
