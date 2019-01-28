#include <iostream>

template <class T>
T Add(T a, T b) {
	return a + b;
}

int main() {
	int resultInt, i1 = 5, i2 = 10; 
	float resultFloat, f1 = 12.2f, f2 = 5.4f;
	resultInt = Add(i1, i2); 
	std::cout << "resultInt = " << resultInt << std::endl; 
	
	resultFloat = Add(f1, f2); 
	std::cout << "resultFloat = " << resultFloat << std::endl;

	return 0;
}
