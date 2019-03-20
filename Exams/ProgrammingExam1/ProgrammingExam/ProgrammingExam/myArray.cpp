#include "MyArray.h"

myArray::myArray()
{
    size = 0;
    capacity = 1;
    numbers = new int[1];
}

int myArray::get_capacity(void) const
{
    return capacity;
}

int myArray::get_size(void) const
{
    return size;
}