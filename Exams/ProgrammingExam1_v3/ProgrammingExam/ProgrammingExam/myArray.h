#pragma once
#include <iostream>

class myArray
{
public:
    myArray(void);

	myArray(const myArray& otherArray);

    int get_capacity(void) const;
    int get_size(void) const;

	void push(int input);

	void pop();

	// Assignment operator
	myArray& operator=(const myArray& rhs);

	// Concatenates a array onto the end of this array.
	myArray& operator+=(const myArray& rhs);

	// Concatenates two arrays.
	myArray operator+(const myArray& rhs) const;

	// Equality operator (Linear time)
	// Both vectors must be the same size.
	bool operator==(const myArray& rhs) const;

	friend std::ostream &operator<<(std::ostream &output, const myArray &m_Array);

private:
	void growArray();

    int *numbers;
    int size;
    int capacity;
};
