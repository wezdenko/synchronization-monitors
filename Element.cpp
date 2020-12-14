#include "headers/Element.hpp"

Element::Element()
{
    this->value = 0;
    this->is_valid = false;
    this->next_elm = nullptr;
}