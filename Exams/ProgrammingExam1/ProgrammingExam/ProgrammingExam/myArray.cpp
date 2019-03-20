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

void myArray::push(int input)
{
}

void myArray::growArray()
{
	//save the original capacity
	unsigned originalCapacity = capacity;

	// Double the capacity
	capacity = (capacity) ? capacity * 2 : 1;

	//allocate a fresh array
	int *freshArray = new int[capacity];

	//copy the data over
	for (unsigned i = 0; i < originalCapacity; i++)
	{
		freshArray[i] = numbers[i];
	}

	//free up the memory and set the array to be the fresh one
	delete numbers;

	numbers = freshArray;
}

std::ostream & operator<<(std::ostream & output, const myArray & m_Array)
{
	// TODO: insert return statement here
	for (int i = 0; i < m_Array.size; i++)
	{
		output << m_Array.numbers[i] << ", ";
	}
	return output;
}
