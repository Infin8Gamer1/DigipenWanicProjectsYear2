/*
File Name = Functions.h
Author = Jacob Holyfield
Date = 1/29/2019
*/

//---------------------------------------------------------------------------
#ifndef FUNCTIONS_H
#define FUNCTIONS_H
//---------------------------------------------------------------------------

namespace CS170
{
	template <class T> 
	void swap(T &left, T &right);
	
	/* 
	 *  Other template function declarations for count, remove, replace, etc.
	 *  go here. Make sure all of your declarations are sorted in alphabetical
	 *  order. This includes putting the swap function above in the proper
	 *  position.
	 *
	 */

	template <class T>
	void display(T* begin, T* end);

	template <class T>
	void swap_ranges(T* begin, T* end, T* other);

	template <class T>
	T* remove(T* begin, T* end, T item);

	template <class T>
	int count(T* begin, T* end, T item);

	template<class T, class T2>
	T* find(T * begin, T * end, T2 item);

	template<class T, class T2>
	T2* copy(T * begin, T * end, T2 * begin2);

	template <class T>
	void fill(T* begin, T* end, T item);
	
	template <class T>
	void replace(T* begin, T* end, T oldItem, T newItem);

	template <class T>
	T* min_element(T* begin, T* end);

	template <class T>
	T* max_element(T* begin, T* end);

	template <class T, class T2>
	bool equal(T* begin, T* end, T2* other);

	template <class T>
	T sum(T* begin, T* end);
}

#include "Functions.cpp"

#endif
//---------------------------------------------------------------------------
