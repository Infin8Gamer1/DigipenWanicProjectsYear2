////////////////////////////////////////////////////////////////////////////////
#ifndef VECTOR_H
#define VECTOR_H
////////////////////////////////////////////////////////////////////////////////

namespace CS170
{

	class SubscriptError
	{
	  public:
		SubscriptError(int Subscript) : subscript_(Subscript) {};
		int GetSubscript(void) const { return subscript_; }

	  private:
		int subscript_;
	};

	template <typename T>
	class Vector
	{
	  public:

		// Default constructor
		Vector(void);

		// Destructor
		~Vector();

		// Adds a node to the back of the array. If there is
		// not enough room in the array, it will be grown to
		// handle more items.
		void push_back(T value);

		// Adds a node to the front of the array. If there is
		// not enough room in the array, it will be grown to
		// handle more items. All items to the right must be
		// shifted over one element to the right.
		void push_front(T value);

		// Subscript operators for const and non-const
		T operator[](unsigned index) const;
		T& operator[](unsigned index);

		// Deletes the underlying array and sets size_ to 0
		void clear(void);

		// Return true if the vector is empty, otherwise, false
		bool empty(void) const;

		// Returns the number of elements in the vector.
		unsigned size(void) const;

		// Returns the size of the underlying array
		unsigned capacity(void) const;

		// The number of memory allocations that have occurred
		unsigned allocations(void) const;

		// Copy constructor
		Vector(const Vector& rhs);

		// Constructor to create a Vector from an array
		Vector(const T array[], unsigned size);

		// Removes the last element. Does nothing if empty.
		void pop_back(void);

		// Removes the first element. Does nothing if empty.
		void pop_front(void);

		// Inserts a new node at the specified position. Now throws an
		// exception if the position is invalid. (Calls check_bounds 
		// which is the function that is actually throwing.)
		void insert(T value, unsigned position);

		// Removes an element with the specified value (first occurrence)
		void remove(T value);

		// Assignment operator
		Vector& operator=(const Vector& rhs);

		// Concatenates a vector onto the end of this vector.
		Vector& operator+=(const Vector& rhs);

		// Concatenates two Vectors.
		Vector operator+(const Vector& rhs) const;

		// Reverses the order of the elements (Linear time)
		void reverse(void);

		// Swaps the contents of other with this Vector (Constant time)
		void swapv(Vector &other);

		// Equality operator (Linear time)
		// Both vectors must be the same size.
		bool operator==(const Vector& rhs) const;

		// Reallocates an array to match the size of the number
		// of elements. If size == capacity, does nothing.
		void shrink_to_fit(void);

	  private:
		T *array_;        // The dynamically allocated array
		unsigned size_;     // The number of elements in the array
		unsigned capacity_; // The allocated size of the array
		unsigned allocs_;   // Number of allocations (resizes)

		// Private methods...
		void check_bounds(unsigned index) const;
		void grow(void);
    
		// Other private methods...
	};

} // namespace CS170

#include "Vector.cpp"

#endif // VECTOR_H
