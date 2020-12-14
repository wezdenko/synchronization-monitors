#pragma once

class Element
{
private:
    int value;
    bool is_valid;
    Element* next_elm;

public:
    Element();

friend class Buffer;
};