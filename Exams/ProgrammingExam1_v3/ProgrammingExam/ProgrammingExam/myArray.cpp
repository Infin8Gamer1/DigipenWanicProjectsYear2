#include "MyArray.h"

myArray::myArray()
{
    size = 0;
    capacity = 1;
    numbers = new int[capacity];
}

myArray::myArray(const myArray & otherArray)
{
	size = 0;
	capacity = otherArray.size;
	numbers = new int[capacity];

	//add elements of other array to this
	for (int i = 0; i < otherArray.size; i++)
	{
		push(otherArray.numbers[i]);
	}
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
	size += 1;

	if (size > capacity)
	{
		growArray();
	}

	numbers[size - 1] = input;
}

void myArray::pop()
{
	size -= 1;
}

myArray & myArray::operator=(const myArray & rhs)
{
	//check if we are trying to assign us to us if we are us then return us however if us isn't them then dont return us and coppy stuff over
	if (this == &rhs) {
		return *this;
	}

	//pop all the elements
	size = 0;
	capacity = rhs.size;
	numbers = new int[capacity];

	//add other elements
	for (int i = 0; i < rhs.size; i++)
	{
		push(rhs.numbers[i]);
	}

	return *this;
}

myArray & myArray::operator+=(const myArray & rhs)
{
	myArray BiggerArray = size < rhs.size ? rhs : *this;
	myArray SmallerArray = size < rhs.size ? *this : rhs;

	//pop all of my elements
	size = 0;

	//reallocate memory for the array if we dont have enough memory
	if (capacity < BiggerArray.size)
	{
		capacity = BiggerArray.size;
		numbers = new int[capacity];
	}

	//add elements from bigger array and smaller array
	for (int i = 0; i < BiggerArray.size; i++)
	{
		if (i < SmallerArray.size)
		{
			push(SmallerArray.numbers[i] + BiggerArray.numbers[i]);
		}
		else {
			push(BiggerArray.numbers[i]);
		}
	}

	return *this;
}

myArray myArray::operator+(const myArray & rhs) const
{
	myArray BiggerArray = size < rhs.size ?  rhs : *this;
	myArray SmallerArray = size < rhs.size ? *this : rhs;

	myArray output = myArray();

	//allocate a fresh array
	output.capacity = BiggerArray.size;
	
	output.numbers = new int[output.capacity];

	//add my elements to the end
	for (int i = 0; i < BiggerArray.size; i++)
	{
		if (i < SmallerArray.size)
		{
			output.push(SmallerArray.numbers[i] + BiggerArray.numbers[i]);
		}
		else {
			output.push(BiggerArray.numbers[i]);
		}
	}

	return output;
}

bool myArray::operator==(const myArray & rhs) const
{
	//if the sizes are not the same then they are diffrent
	if (size != rhs.size)
	{
		return false;
	}

	//check each element in the arrays if any of them are diffrent then they arent equal
	for (int i = 0; i < size; i++)
	{
		if (numbers[i] != rhs.numbers[i]) {
			return false;
		}
	}

	return true;
}

std::ostream & operator<<(std::ostream & output, const myArray & m_Array)
{
	// TODO: insert return statement here
	for (int i = 0; i < m_Array.size; i++)
	{
		output << m_Array.numbers[i] << " ";
	}

	output << std::endl;

	return output;
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


