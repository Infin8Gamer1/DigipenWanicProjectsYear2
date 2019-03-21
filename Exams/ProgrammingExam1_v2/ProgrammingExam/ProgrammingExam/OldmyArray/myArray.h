#pragma once
#include <iostream>

class myArray
{
public:
    myArray(void);

    int get_capacity(void) const;
    int get_size(void) const;

private:
    int *numbers;
    int size;
    int capacity;
};
