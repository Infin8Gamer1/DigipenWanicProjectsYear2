#pragma once
#include <iostream>

class myArray
{
public:
    myArray(void);

    int get_capacity(void) const;
    int get_size(void) const;

	void push(int input);

	friend std::ostream &operator<<(std::ostream &output, const myArray &m_Array);

private:
	void growArray();

    int *numbers;
    int size;
    int capacity;
};
