#include "headers/BufferMonitor.hpp"

BufferMonitor::BufferMonitor()
{

}

void BufferMonitor::putEven(int value)
{
    this->enter();
    if (!this->canPutEven())
        this->wait(putEvenCond);

    this->buffer.put(value);

    // przekazanie sekcji krytycznej
    if (this->putOddCond.getWaiting() > 0 && this->canPutOdd())
        putOddCond.signal();
    else if (this->getEvenCond.getWaiting() > 0 && this->canGetEven())
        getEvenCond.signal();
    else if (this->getOddCond.getWaiting() > 0 && this->canGetOdd())
        getOddCond.signal();
    else
        this->leave();
    
}

void BufferMonitor::putOdd(int value)
{
    this->enter();
    if (!this->canPutOdd())
        this->wait(putOddCond);

    this->buffer.put(value);

    // przekazanie sekcji krytycznej
    if (this->putEvenCond.getWaiting() > 0 && this->canPutEven())
        putEvenCond.signal();
    else if (this->getEvenCond.getWaiting() > 0 && this->canGetEven())
        getEvenCond.signal();
    else if (this->getOddCond.getWaiting() > 0 && this->canGetOdd())
        getOddCond.signal();
    else
        this->leave();

}

int BufferMonitor::getOdd()
{
    this->enter();
    if (!this->canGetOdd())
        this->wait(getOddCond);

    int value = this->buffer.get();

    // przekazanie sekcji krytycznej
    if (this->putEvenCond.getWaiting() > 0 && this->canPutEven())
        putEvenCond.signal();
    else if (this->putOddCond.getWaiting() > 0 && this->canPutOdd())
        putOddCond.signal();
    else if (this->getOddCond.getWaiting() > 0 && this->canGetOdd())
        getOddCond.signal();
    else
        this->leave();

    return value;
}

int BufferMonitor::getEven()
{
    this->enter();
    if (!this->canGetEven())
        this->wait(getEvenCond);

    int value = this->buffer.get();

    // przekazanie sekcji krytycznej
    if (this->putEvenCond.getWaiting() > 0 && this->canPutEven())
        putEvenCond.signal();
    else if (this->putOddCond.getWaiting() > 0 && this->canPutOdd())
        putOddCond.signal();
    else if (this->getEvenCond.getWaiting() > 0 && this->canGetEven())
        getEvenCond.signal();
    else
        this->leave();

    return value;
}

bool BufferMonitor::canPutEven() const
{
    if (this->buffer.getEven() < 10)
        return true;
    return false;
}

bool BufferMonitor::canGetEven() const
{
    if (this->buffer.getLength() >= 3 && this->buffer.check() % 2 == 0)
        return true;
    return false;
}

bool BufferMonitor::canPutOdd() const
{
    if (this->buffer.getEven() > (this->buffer.getLength() - this->buffer.getEven()))
        return true;
    return false;
}

bool BufferMonitor::canGetOdd() const
{
    if (this->buffer.getLength() >= 7 && this->buffer.check() % 2 == 1)
        return true;
    return false;
}
