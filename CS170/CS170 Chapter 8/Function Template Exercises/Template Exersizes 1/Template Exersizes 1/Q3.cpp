#include <iostream>

template <class T1, class T2>
double Average(T1 a, T2 b) {
	return (a + b)/2.0;
}

int main() {
	int i1 = 5, i2 = 10;
	float f = 12.2f;
	double result, d = 5.7;
	
	result = Average(i1, i2); 
	std::cout << "result = " << result << std::endl; 
	
	result = Average(i1, f);
	std::cout << "result = " << result << std::endl;
	
	result = Average(d, f); 
	std::cout << "result = " << result << std::endl;

	getchar();

	return 0;
}
