/*
Author - Jacob Holyfield
Date - 1/9/2019
Other information - SpaceX has an iridium flight scheduled for 1/11/19
*/

#include <iostream>  // cout
#include <cstdlib>   // abort
#include "Vector.h"

namespace CS170
{
	Vector::Vector(void) : array_(0), size_(0), capacity_(0), allocs_(0)
	{}

	Vector::~Vector()
	{
		clear();
	}

	Vector::Vector(const Vector & rhs)
	{
		allocs_ += 1;

		size_ = 0;

		capacity_ = rhs.size_;

		//allocate a fresh array
		array_ = new int[capacity_];

		for (unsigned i = 0; i < rhs.size_; i++)
		{
			push_back(rhs.array_[i]);
		}
	}

	Vector::Vector(const int array[], unsigned size)
	{
		allocs_ += 1;

		capacity_ = size;

		//allocate a fresh array
		array_ = new int[capacity_];

		for (unsigned i = 0; i < size; i++)
		{
			push_back(array[i]);
		}
	}

	void Vector::push_back(int value)
	{
		//add one to the size as we are adding a value
		size_ += 1;

		//check if the array needs to grow and call grow if it does
		if (capacity_ < size_) {
			grow();
		}

		//put the value in the array!
		array_[size_ - 1] = value;
	}

	void Vector::push_front(int value)
	{
		//add one to the size as we are adding a value
		size_ += 1;

		//check if the array needs to grow and call grow if it does
		if (capacity_ < size_) {
			grow();
		}

		//loop through the array from right to left and shift values
		for (int i = size_ - 2; i >= 0; i--)
		{
			array_[i + 1] = array_[i];
		}

		//set the first value to 0
		array_[0] = value;
	}

	void Vector::pop_back(void)
	{
		size_ -= 1;
	}

	void Vector::pop_front(void)
	{
		for (unsigned i = 1; i < size_; i++)
		{
			array_[i - 1] = array_[i];
		}

		size_ -= 1;
	}

	void Vector::insert(int value, unsigned position)
	{
		if (position >= size_) {
			push_back(value);
		} else if (position <= 0) {
			push_front(value);
		} else {
			//add one to the size as we are adding a value
			size_ += 1;

			//check if the array needs to grow and call grow if it does
			if (capacity_ < size_) {
				grow();
			}

			//shift everything down to make room at the position
			for (unsigned i = size_ - 2; i >= position; i--)
			{
				array_[i + 1] = array_[i];
			}

			//put the value in the array
			array_[position] = value;
		}
		
		
	}

	void Vector::remove(int value)
	{
		int numRemoved = 0;

		int* newEnd = array_;
		int* begin = array_;
		int* end = array_ + size_;

		while (begin != end) {

			if (*begin != value) {
				//copy begins value over to newEnd
				*newEnd = *begin;
				//move new end up
				newEnd++;
			} else {
				numRemoved += 1;
			}

			//move begin up
			begin++;
		}

		size_ -= numRemoved;
	}

	void Vector::clear(void)
	{
		delete array_;
		array_ = nullptr;
		size_ = 0;
		capacity_ = 0;
	}

	bool Vector::empty(void) const
	{
		//return true if the size is zero
		return size_ == 0;
	}

	Vector & Vector::operator=(const Vector & rhs)
	{
		//pop all the elements
		size_ = 0;

		//check if we need to allocate new memory
		if (capacity_ < rhs.size_) {
			allocs_ += 1;

			capacity_ = rhs.size_;

			//allocate a fresh array
			array_ = new int[capacity_];
		}
		
		//add other elements
		for (unsigned i = 0; i < rhs.size_; i++)
		{
			push_back(rhs.array_[i]);
		}
		
		return *this;
	}

	Vector & Vector::operator+=(const Vector & rhs)
	{
		//check if we need to allocate new memory
		if (capacity_ < rhs.size_ + size_) {
			allocs_ += 1;

			//save the original capacity
			int originalCapacity = capacity_;

			capacity_ = rhs.size_ + size_;

			//allocate a fresh array
			int *freshArray = new int[capacity_];

			//copy the data over
			for (int i = 0; i < originalCapacity; i++)
			{
				freshArray[i] = array_[i];
			}

			//free up the memory and set the array to be the fresh one
			delete array_;

			array_ = freshArray;
		}

		//add other elements to the end
		unsigned size = rhs.size_;

		for (unsigned i = 0; i < size; i++)
		{
			push_back(rhs.array_[i]);
		}

		return *this;
	}

	Vector Vector::operator+(const Vector & rhs) const
	{

		Vector output = Vector();

		//check if we need to allocate new memory
		if (output.capacity_ < rhs.size_ + size_) {
			output.allocs_ += 1;

			output.capacity_ = rhs.size_ + size_;

			//allocate a fresh array
			output.array_ = new int[output.capacity_];
		}

		//add my elements to the end
		for (unsigned i = 0; i < size_; i++)
		{
			output.push_back(array_[i]);
		}

		//add others elements to the end
		for (unsigned i = 0; i < rhs.size_; i++)
		{
			output.push_back(rhs.array_[i]);
		}

		
		return output;
	}

	int Vector::operator[](unsigned index) const
	{
		return array_[index];
	}

	int & Vector::operator[](unsigned index)
	{
		return array_[index];
	}

	unsigned Vector::size(void) const
	{
		return size_;
	}

	unsigned Vector::capacity(void) const
	{
		return capacity_;
	}

	unsigned Vector::allocations(void) const
	{
		return allocs_;
	}


	///////////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////////
	// private 
	///////////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////////

	void Vector::check_bounds(unsigned index) const
	{
		// Don't have to check for < 0 because index is unsigned
		if (index >= size_)
		{
			std::cout << "Attempting to access index " << index << ".";
			std::cout << " The size of the array is " << size_ << ". Aborting...\n";
			std::abort();
		}
	}

	void Vector::grow(void)
	{
		allocs_ += 1;

		//save the original capacity
		int originalCapacity = capacity_;

		// Double the capacity
		capacity_ = (capacity_) ? capacity_ * 2 : 1;
    
		//allocate a fresh array
		int *freshArray = new int[capacity_];

		//copy the data over
		for (int i = 0; i < originalCapacity; i++)
		{
			freshArray[i] = array_[i];
		}

		//free up the memory and set the array to be the fresh one
		delete array_;

		array_ = freshArray;
	}

} // namespace CS170