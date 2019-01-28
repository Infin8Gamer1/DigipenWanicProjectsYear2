#include <iostream>

template <class T1, class T2>
double Average(T1 a, T2 b) {
	return (a + b)/2.0;
}

template<>
double Average<int*, int>(int* a, int b) {
	double total = 0;

	for (int i = 0; i < b; i++)
	{
		total += a[i];
	}

	return (double)(total / b);
}

template<>
double Average<float*, int>(float* a, int b) {
	double total = 0;

	for (int i = 0; i < b; i++)
	{
		total += a[i];
	}

	return (double)(total / b);
}

int main() {
	int i1 = 5, i2 = 10;
	float f = 12.2f;
	double result, d = 5.7;
	int num1[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
	float num2[] = { 1.4f, 2.3f, 4.3f, 6.0f };

	result = Average(i1, i2);
	std::cout << "result = " << result << std::endl;
	
	result = Average(i1, f);
	std::cout << "result = " << result << std::endl;
	
	result = Average(d, f);
	std::cout << "result = " << result << std::endl;
	
	result = Average(num1, 10);
	std::cout << "result = " << result << std::endl;
	
	result = Average(num2, 4);
	std::cout << "result= " << result << std::endl;

	getchar();

	return 0;
}
