#include <iostream>

template <class T>
int my_compare(T a, T b) {
	
	if (a == b) {
		return 0;
	} else if (a < b) {
		return -1;
	} else {
		return 1;
	}
}

template<>
int my_compare<const char*>(const char* a, const char* b) {
	return strcmp(a, b);
}

int main() {
	int result = 0; 
	int i1 = 5, i2 = 10, i3 = 5; 
	float f1 = 12.2f, f2 = 13.5f; 
	const char sentence1[] = "Hello"; 
	const char sentence2[] = "World"; 
	const char sentence3[] = "Hello";


	std::cout << my_compare(i1, i2) << std::endl;
	std::cout << my_compare(i2, i3) << std::endl;
	std::cout << my_compare(i1, i3) << std::endl;
	std::cout << my_compare(f1, f2) << std::endl;

	std::cout << my_compare(sentence1, sentence2) << std::endl;
	std::cout << my_compare(sentence1, sentence3) << std::endl;

	getchar();

	return 0;
}
