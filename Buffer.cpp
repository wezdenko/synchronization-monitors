#include "headers/Buffer.hpp"

Buffer::Buffer()
{
    this->head = nullptr;
    this->tail = nullptr;
    this->length = 0;
    this->even = 0;
}

void Buffer::put(int value)
{
    int free_index;

    for (int i = 0; i < MAXSIZE; i++)
    {
        if (this->queue[i].is_valid == false)
        {
            free_index = i;
            break;
        }
    }

    if (this->head == 0)
    {
        this->head = &this->queue[free_index];
        this->tail = &this->queue[free_index];
    }
    else
    {
        this->tail->next_elm = &this->queue[free_index];
        this->tail = &this->queue[free_index];
    }

    this->queue[free_index].value = value;
    this->queue[free_index].is_valid = true;
    this->queue[free_index].next_elm = nullptr;

    if (value % 2 == 0)
        this->even++;
    this->length++;
}

int Buffer::get()
{
    int ret_value = this->head->value;

    this->head->is_valid = false;
    this->head = this->head->next_elm;
    this->length--;

    if (ret_value % 2 == 0)
        this->even--;

    return ret_value;
}

int Buffer::check() const
{
    return this->head->value;
}

int Buffer::getLength() const
{
    return this->length;
}

int Buffer::getEven() const
{
    return this->even;
}
