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

	int Vector::operator[](unsigned index) const
	{
		return array_[index];
	}

	int & Vector::operator[](unsigned index)
	{
		return array_[index];
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