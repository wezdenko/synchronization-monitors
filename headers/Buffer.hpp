#pragma once
#include "Element.hpp"

class Buffer
{
private:
    static const int MAXSIZE = 20;

    Element queue[20];
    Element* head;
    Element* tail;
    int length;
    int even;

public:
    Buffer();

    int get();
    void put(int value);

    int check() const;
    int getLength() const;
    int getEven() const;
};
