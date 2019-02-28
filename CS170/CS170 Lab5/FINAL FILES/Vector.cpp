/*
Author - Jacob Holyfield
Date - 2/25/2019
Random SpaceX fact - Spacex is testing the Crew Dragon this Month! The first demo flight should happen in Febuary 2019!
*/

#include <iostream>  // cout
#include <cstdlib>   // abort
#include "Vector.h"

namespace CS170
{

	template <typename T>
	Vector<T>::Vector(void) : array_(), size_(0), capacity_(0), allocs_(0)
	{}

	template <typename T>
	Vector<T>::~Vector()
	{
		clear();
	}

	template <typename T>
	Vector<T>::Vector(const Vector & rhs) : array_(), size_(0), capacity_(0), allocs_(0)
	{
		allocs_ += 1;

		capacity_ = rhs.size_;

		//allocate a fresh array
		array_ = new T[capacity_];

		//add elements of other array to this
		for (unsigned i = 0; i < rhs.size_; i++)
		{
			push_back(rhs.array_[i]);
		}
	}

	template <typename T>
	Vector<T>::Vector(const T array[], unsigned size) : array_(), size_(0), capacity_(0), allocs_(0)
	{
		allocs_ += 1;

		capacity_ = size;

		//allocate a fresh array
		array_ = new T[capacity_];

		//add elements of the array to this
		for (unsigned i = 0; i < size; i++)
		{
			push_back(array[i]);
		}
	}

	template <typename T>
	void Vector<T>::push_back(T value)
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

	template <typename T>
	void Vector<T>::push_front(T value)
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

	template <typename T>
	void Vector<T>::pop_back(void)
	{
		size_ -= 1;
	}

	template <typename T>
	void Vector<T>::pop_front(void)
	{
		for (unsigned i = 1; i < size_; i++)
		{
			array_[i - 1] = array_[i];
		}

		size_ -= 1;
	}

	template <typename T>
	void Vector<T>::insert(T value, unsigned position)
	{
		check_bounds(position);

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

	template <typename T>
	void Vector<T>::remove(T value)
	{
		int numRemoved = 0;

		T* newEnd = array_;
		T* begin = array_;
		T* end = array_ + size_;

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

	template <typename T>
	void Vector<T>::clear(void)
	{
		delete array_;
		array_ = nullptr;
		size_ = 0;
		capacity_ = 0;
	}

	template <typename T>
	bool Vector<T>::empty(void) const
	{
		//return true if the size is zero
		return size_ == 0;
	}

	template <typename T>
	Vector<T> & Vector<T>::operator=(const Vector & rhs)
	{
		//check if we are trying to assign us to us if we are us then return us however if us isn't them then dont return us and coppy stuff over
		if (this == &rhs) {
			return *this;
		}

		//pop all the elements
		size_ = 0;

		//check if we need to allocate new memory
		if (capacity_ < rhs.size_) {
			allocs_ += 1;

			capacity_ = rhs.size_;

			//allocate a fresh array
			array_ = new T[capacity_];
		}
		
		//add other elements
		for (unsigned i = 0; i < rhs.size_; i++)
		{
			push_back(rhs.array_[i]);
		}
		
		return *this;
	}

	template <typename T>
	Vector<T> & Vector<T>::operator+=(const Vector & rhs)
	{
		//check if we need to allocate new memory
		if (capacity_ < rhs.size_ + size_) {
			allocs_ += 1;

			//save the original capacity
			int originalCapacity = capacity_;

			capacity_ = rhs.size_ + size_;

			//allocate a fresh array
			T *freshArray = new T[capacity_];

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

	template <typename T>
	Vector<T> Vector<T>::operator+(const Vector & rhs) const
	{

		Vector output = Vector();

		//allocate new memory
		output.allocs_ += 1;

		output.capacity_ = rhs.size_ + size_;

		//allocate a fresh array
		output.array_ = new T[output.capacity_];
		

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

	template<typename T>
	void Vector<T>::reverse(void)
	{
		if (size_ == 0)
		{
			return;
		}
		
		unsigned start = 0;
		unsigned end = size_ - 1;

		while (start < end)
		{
			int temp = array_[start];
			array_[start] = array_[end];
			array_[end] = temp;
			start++;
			end--;
		}
	}

	template <typename T>
	void swap(T &a, T& b)
	{
		T temp = a;
		a = b;
		b = temp;
	}

	template<typename T>
	void Vector<T>::swapv(Vector & other)
	{
		//swap all the things
		swap(size_, other.size_);
		swap(capacity_, other.capacity_);
		swap(allocs_, other.allocs_);
		swap(array_, other.array_);
	}

	template<typename T>
	bool Vector<T>::operator==(const Vector & rhs) const
	{
		//if the sizes are not the same then they are diffrent
		if (size_ != rhs.size_)
		{
			return false;
		}

		//check each element in the arrays if any of them are diffrent then they arent equal
		for (unsigned i = 0; i < size_; i++)
		{
			if (array_[i] != rhs.array_[i]) {
				return false;
			}
		}
		
		return true;
	}

	template<typename T>
	void Vector<T>::shrink_to_fit(void)
	{
		if (size_ == capacity_)
		{
			return;
		}

		allocs_++;

		T* oldArray = array_;
		unsigned oldSize = size_;

		array_ = new T[oldSize];
		capacity_ = oldSize;
		size_ = 0;

		for (unsigned i = 0; i < oldSize; i++)
		{
			push_back(oldArray[i]);
		}
	}

	template <typename T>
	T Vector<T>::operator[](unsigned index) const
	{
		check_bounds(index);

		return array_[index];
		
	}

	template <typename T>
	T & Vector<T>::operator[](unsigned index)
	{
		check_bounds(index);

		return array_[index];
	}

	template <typename T>
	unsigned Vector<T>::size(void) const
	{
		return size_;
	}

	template <typename T>
	unsigned Vector<T>::capacity(void) const
	{
		return capacity_;
	}

	template <typename T>
	unsigned Vector<T>::allocations(void) const
	{
		return allocs_;
	}


	///////////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////////
	// private 
	///////////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////////

	template <typename T>
	void Vector<T>::check_bounds(unsigned index) const
	{
		// Don't have to check for < 0 because index is unsigned
		if (index >= size_)
		{
			/*std::cout << "Attempting to access index " << index << ".";
			std::cout << " The size of the array is " << size_ << ". Aborting...\n";
			std::abort();*/

			throw SubscriptError(index);
		}
	}

	template <typename T>
	void Vector<T>::grow(void)
	{
		allocs_ += 1;

		//save the original capacity
		unsigned originalCapacity = capacity_;

		// Double the capacity
		capacity_ = (capacity_) ? capacity_ * 2 : 1;
    
		//allocate a fresh array
		T *freshArray = new T[capacity_];

		//copy the data over
		for (unsigned i = 0; i < originalCapacity; i++)
		{
			freshArray[i] = array_[i];
		}

		//free up the memory and set the array to be the fresh one
		delete array_;

		array_ = freshArray;
	}

} // namespace CS170