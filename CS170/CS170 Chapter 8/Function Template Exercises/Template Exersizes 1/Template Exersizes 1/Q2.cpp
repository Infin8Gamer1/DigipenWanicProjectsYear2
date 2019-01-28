#include <iostream>

template <class T>
T Add(T a, T b) {
	return a + b;
}

template <class T1, class T2, class T3>
T3 Add(T1 a, T2 b) {
	return a + b;
}

int main() {
	int resultInt, i1 = 5, i2 = 10;
	float resultFloat, f1 = 12.2f, f2 = 5.4f;
	double resultDouble, d = 5.7; 
	
	resultInt = Add<int>(i1, i2); 
	std::cout << "resultInt = " << resultInt << std::endl; 
	
	resultFloat = Add<float>(f1, f2); 
	std::cout << "resultFloat = " << resultFloat << std::endl; 
	
	resultDouble = Add<double>(i1, d); 
	std::cout << "resultDouble = " << resultDouble << std::endl; 
	
	resultInt = Add<int, float, int>(f1, i1); 
	//will cause a warning
	std::cout <<"resultInt = "<<resultInt <<std::endl;

	getchar();

	return 0;
}
