/*
	File Name = Functions.cpp
	Author = Jacob Holyfield
	Date = 1/29/2019
*/

#include "Functions.h"
#include <iostream> // cout, endl

namespace CS170
{
	/******************************************************************************/
	/*!
	  \brief
		Swaps two objects. There is no return value but the two objects are
		swapped in place.
	  
	  \param left
		The first object to swap.
	  
	  \param right
		The second object to swap.
	*/
	/******************************************************************************/
	template <class T> 
	void swap(T &left, T &right)
	{
	  T temp = right; // need a temporary copy
	  right = left;
	  left = temp;
	}

	/******************************************************************************/
	/*!
	\brief
	Displays two elements

	\param begin
	The begining of the array.

	\param end
	The end of the array.
	*/
	/******************************************************************************/
	template<class T>
	void display(T * begin, T * end)
	{
		while (begin != end)
		{
			if (begin + 1 != end) {
				std::cout << *begin << ", ";
			}
			else {
				std::cout << *begin;
			}
			
			begin++;
		}

		std::cout << std::endl;
	}

	/******************************************************************************/
	/*!
	\brief
	Swaps the arrays.

	\param begin
	The begining of the array.

	\param end
	The end of the array.

	\param other
	The begining of the other array.
	*/
	/******************************************************************************/
	template<class T>
	void swap_ranges(T * begin, T * end, T * other)
	{
		while (begin != end)
		{
			swap(*begin, *other);
			begin++;
			other++;
		}
	}

	/******************************************************************************/
	/*!
	\brief
	Removes all the elements that match the item

	\param begin
	The begining of the array.

	\param end
	The end of the array.

	\param item
	The value that should be removed
	*/
	/******************************************************************************/
	template<class T>
	T* remove(T * begin, T * end, T item)
	{
		T* newEnd = begin;

		while (begin != end) {
			
			if (*begin != item) {
				//copy begins value over to newEnd
				*newEnd = *begin;
				//move new end up
				newEnd++;
			}

			//move begin up
			begin++;
		}

		return newEnd;
	}

	/******************************************************************************/
	/*!
	\brief
	Counts the number of occurances of item in the array

	\param begin
	The begining of the array.

	\param end
	The end of the array.

	\param item
	The value that is being counted
	*/
	/******************************************************************************/
	template<class T>
	int count(T * begin, T * end, T item)
	{
		int num = 0;

		while (begin != end)
		{
			if (*begin == item) {
				num += 1;
			}

			begin++;
		}

		return num;
	}

	/******************************************************************************/
	/*!
	\brief
	Returns a pointer to the first accurance of the item

	\param begin
	The begining of the array.

	\param end
	The end of the array.

	\param item
	The value that should be looked for
	*/
	/******************************************************************************/
	template<class T, class T2>
	T * find(T * begin, T * end, T2 item)
	{
		while (begin != end)
		{
			if (*begin == item) {
				return begin;
			}

			begin++;
		}
		
		return end;
	}

	/******************************************************************************/
	/*!
	\brief
	Copies all of the items from one array to another

	\param begin
	The begining of the array.

	\param end
	The end of the array.

	\param begin2
	The begining of the second array
	*/
	/******************************************************************************/
	template<class T, class T2>
	T2* copy(T * begin, T * end, T2 * begin2)
	{
		while (begin != end)
		{
			//set begin 2 to begin therefor copying begin to begin 2
			*begin2 = *begin;

			begin++;
			begin2++;
		}
		
		return begin2;
	}

	/******************************************************************************/
	/*!
	\brief
	fills the array with items

	\param begin
	The begining of the array.

	\param end
	The end of the array.

	\param item
	The value that should be filling the array
	*/
	/******************************************************************************/
	template<class T>
	void fill(T * begin, T * end, T item)
	{
		while (begin != end)
		{
			*begin = item;
			begin++;
		}
	}

	/******************************************************************************/
	/*!
	\brief
	Replaces all occurances of oldItem with newItem

	\param begin
	The begining of the array.

	\param end
	The end of the array.

	\param oldItem
	The value that is being replaced

	\param newItem
	The value that is replacing the old value
	*/
	/******************************************************************************/
	template<class T>
	void replace(T * begin, T * end, T oldItem, T newItem)
	{
		while (begin != end)
		{
			if (*begin == oldItem) {
				*begin = newItem;
			}

			begin++;
		}
	}


	/******************************************************************************/
	/*!
	\brief
	finds the smallest element and returns a pointer to it

	\param begin
	The begining of the array.

	\param end
	The end of the array.
	*/
	/******************************************************************************/
	template<class T>
	T * min_element(T * begin, T * end)
	{
		T* tempMin = begin;

		while (begin != end)
		{
			if (*begin < *tempMin) {
				tempMin = begin;
			}

			begin++;
		}
		
		return tempMin;
	}

	/******************************************************************************/
	/*!
	\brief
	finds the bigest element and returns a pointer to it

	\param begin
	The begining of the array.

	\param end
	The end of the array.
	*/
	/******************************************************************************/
	template<class T>
	T * max_element(T * begin, T * end)
	{
		T* tempMax = begin;

		while (begin != end)
		{
			if (*begin > *tempMax) {
				tempMax = begin;
			}

			begin++;
		}

		return tempMax;
	}

	/******************************************************************************/
	/*!
	\brief
	compares arrays and determines if they are equal

	\param begin
	The begining of the array.

	\param end
	The end of the array.

	\param other
	The other array that is being compared to
	*/
	/******************************************************************************/
	template<class T, class T2>
	bool equal(T * begin, T * end, T2 * other)
	{
		while (begin != end)
		{
			if (*begin != *other) {
				return false;
			}
			else {
				begin++;
				other++;
			}
		}

		return true;
	}

	/******************************************************************************/
	/*!
	\brief
	Returns the sum of all the elements in the array

	\param begin
	The begining of the array.

	\param end
	The end of the array.
	*/
	/******************************************************************************/
	template<class T>
	T sum(T * begin, T * end)
	{
		T total = T();
		
		while (begin != end)
		{
			total = total + *begin;

			begin++;
		}

		return total;
	}

}