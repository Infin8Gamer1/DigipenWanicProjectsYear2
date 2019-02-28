#include <iostream> // cout, endl
#include <cstdio>   // sprintf
#include <cstring>  // strcpy
#include <cstdlib>  // atoi

#include "Vector.h"

// PERSON STRUCT AND HELPER FUNCTIONS
const unsigned ID_LEN = 6;
struct Person
{
	char ID[ID_LEN + 1];
	char lastName[26];
	char firstName[26];
	float salary;
	unsigned years;
};

struct Person PEOPLE[] =
{
  {"101000", "Last",       "First",        0,  0},
  {"101001", "Faith",      "Ian",      80000, 10},
  {"102001", "Tufnel",     "Nigel",    90000, 12},
  {"103001", "Savage",     "Viv",      50000,  4},
  {"104001", "Shrimpton",  "Mick",     50000,  4},
  {"105001", "Besser",     "Joe",      40000,  1},
  {"106001", "Smalls",     "Derek",    80000, 10},
  {"107001", "St.Hubbins", "David",    90000, 12},
  {"108001", "Fleckman",   "Bobbi",   120000,  8},
  {"109001", "Eton-Hogg",  "Denis",   250000, 22},
  {"110001", "Upham",      "Danny",    60000,  5},
  {"111001", "McLochness", "Ross",     60000,  5},
  {"112001", "Pudding",    "Ronnie",   50000,  2},
  {"113001", "Schindler",  "Danny",    60000,  3},
  {"114001", "Pettibone",  "Jeanine",  85000,  3},
  {"115001", "Fame",       "Duke",     95000,  8},
  {"116001", "Fufkin",     "Artie",    45000,  1},
  {"117001", "DiBergi",    "Marty",    15000,  7},
  {"118001", "Floyd",      "Pink",     25000,  6},
  {"119001", "Zeppelin",   "Led",      35000,  3},
  {"120001", "Mason",      "Nick",     15000,  7},
  {"121001", "Wright",     "Richard",  17000,  9},
  {"122001", "Waters",     "Roger",    10000,  3},
  {"123001", "Gilmore",    "David",    19000,  5}
};

Person **PersonRecs;

void FreePersonRecs(void)
{
	unsigned count = sizeof(PEOPLE) / sizeof(*PEOPLE);

	for (unsigned i = 0; i < count; i++)
		delete PersonRecs[i];

	delete[] PersonRecs;
}

void FillPersonRecs(void)
{
	unsigned count = sizeof(PEOPLE) / sizeof(*PEOPLE);
	PersonRecs = (Person **) new Person[count];

	unsigned index = 0;
	for (unsigned i = 0; i < count; i++)
	{
		Person *person = new Person;
		strcpy(person->ID, PEOPLE[i].ID);
		strcpy(person->lastName, PEOPLE[i].lastName);
		strcpy(person->firstName, PEOPLE[i].firstName);
		person->salary = PEOPLE[i].salary;
		person->years = PEOPLE[i].years;
		PersonRecs[index++] = person;
	}
}

const unsigned MAX_PERSONS = 10000;
const unsigned NUM_PEOPLE = sizeof(PEOPLE) / sizeof(*PEOPLE);

std::ostream& operator<<(std::ostream &os, const Person &person)
{
	char buffer[200];
	std::sprintf(buffer, "Key: %8s, Name: %12s, %12s    Salary:%7.0f, Years: %2d\n",
		person.ID, person.lastName, person.firstName, person.salary,
		person.years);
	os << buffer;
	return os;
}

// VECTOR HELPER FUNCTIONS
template <typename T>
std::ostream& operator<<(std::ostream &os, const CS170::Vector<T>& array)
{
	for (unsigned i = 0; i < array.size(); i++)
	{
		os << array[i];
	}

	os << "(size=" << array.size() << ", capacity=" <<
		array.capacity() << ", allocs=" <<
		array.allocations() << ")";
	os << std::endl << std::endl;
	return os;
}

// DRIVER FUNCTIONS
void TestPushFront(void)
{
	std::cout << "TestPushFront..." << std::endl;

	int size = 5;
	CS170::Vector<Person> vector;
	for (int i = 1; i <= size; i++)
		vector.push_front(*PersonRecs[i]);

	std::cout << vector;
	std::cout << "Items in the vector: " << vector.size() << std::endl;
	std::cout << std::endl;
}

void TestPushBack(void)
{
	std::cout << "TestPushBack..." << std::endl;

	int size = 5;
	CS170::Vector<Person> vector;
	for (int i = 1; i <= size; i++)
		vector.push_back(*PersonRecs[i]);

	std::cout << vector;
	std::cout << "Items in the vector: " << vector.size() << std::endl;
	std::cout << std::endl;
}

void TestPushFrontBack(void)
{
	std::cout << "TestPushFrontBack..." << std::endl;

	int size = 5;
	CS170::Vector<Person> vector;
	for (int i = 1; i <= size; i++)
	{
		vector.push_front(*PersonRecs[i]);
		vector.push_back(*PersonRecs[i + 10]);
	}

	std::cout << vector;
	std::cout << "Items in the vector: " << vector.size() << std::endl;
	std::cout << std::endl;
}

void TestPopFront(void)
{
	std::cout << "TestPopFront..." << std::endl;

	int size = 5;
	CS170::Vector<Person> vector;
	for (int i = 1; i <= size; i++)
		vector.push_front(*PersonRecs[i]);

	std::cout << vector;
	while (!vector.empty())
	{
		Person item = vector[0];
		vector.pop_front();
		std::cout << "First item was: " << item << std::endl;
		std::cout << "New vector:\n";
		std::cout << vector;
		std::cout << "Items in the vector: " << vector.size() << std::endl;
	}
	std::cout << std::endl;
}

void TestArray1(void)
{
	std::cout << "TestArray1..." << std::endl;
	Person array[] = { {"101001", "Faith",      "Ian",      80000, 10},
					  {"102001", "Tufnel",     "Nigel",    90000, 12},
					  {"103001", "Savage",     "Viv",      50000,  4},
					  {"104001", "Shrimpton",  "Mick",     50000,  4},
					  {"105001", "Besser",     "Joe",      40000,  1},
					  {"106001", "Smalls",     "Derek",    80000, 10},
					  {"107001", "St.Hubbins", "David",    90000, 12},
					  {"108001", "Fleckman",   "Bobbi",   120000,  8},
					  {"109001", "Eton-Hogg",  "Denis",   250000, 22},
					  {"110001", "Upham",      "Danny",    60000,  5}
	};

	int size = sizeof(array) / sizeof(*array);

	// Construct from array
	CS170::Vector<Person> vector(array, size);

	std::cout << vector;
	std::cout << "Items in the vector: " << vector.size() << std::endl;
	std::cout << std::endl;
}

void TestArray2(void)
{
	std::cout << "TestArray2..." << std::endl;

	const
		Person array[] = { {"101001", "Faith",      "Ian",      80000, 10},
						  {"102001", "Tufnel",     "Nigel",    90000, 12},
						  {"103001", "Savage",     "Viv",      50000,  4},
						  {"104001", "Shrimpton",  "Mick",     50000,  4},
						  {"105001", "Besser",     "Joe",      40000,  1},
						  {"106001", "Smalls",     "Derek",    80000, 10},
						  {"107001", "St.Hubbins", "David",    90000, 12},
						  {"108001", "Fleckman",   "Bobbi",   120000,  8},
						  {"109001", "Eton-Hogg",  "Denis",   250000, 22},
						  {"110001", "Upham",      "Danny",    60000,  5}
	};

	int size = sizeof(array) / sizeof(*array);

	// Construct from array
	CS170::Vector<Person> vector(array, size);

	std::cout << vector;
	std::cout << "Items in the vector: " << vector.size() << std::endl;
	std::cout << std::endl;
}

void TestCopyConstructor1(void)
{
	std::cout << "TestCopyConstructor1..." << std::endl;
	int size = 10;
	CS170::Vector<Person> vector1;
	for (int i = 1; i <= size; i++)
		vector1.push_front(*PersonRecs[i]);

	std::cout << "Vector 1:\n";
	std::cout << vector1;

	CS170::Vector<Person> vector2(vector1);
	std::cout << "Vector 2:\n";
	std::cout << vector2;

	std::cout << std::endl;
}

void TestCopyConstructor2(void)
{
	std::cout << "TestCopyConstructor2..." << std::endl;
	int size = 10;
	CS170::Vector<Person> vector1;
	for (int i = 1; i <= size; i++)
		vector1.push_front(*PersonRecs[i]);

	std::cout << "Vector 1:\n";
	std::cout << vector1;

	const CS170::Vector<Person> vector2(vector1);
	std::cout << "Vector 2:\n";
	std::cout << vector2;

	if (vector2.empty())
		std::cout << "Vector 2 is empty\n";
	else
		std::cout << "Vector 2 is not empty\n";

	std::cout << "Items in Vector2: ";
	std::cout << vector2.size();
	std::cout << std::endl;

	std::cout << std::endl;
}

void TestAssignment1(void)
{
	std::cout << "TestAssignment1..." << std::endl;
	int size = 10;
	CS170::Vector<Person> vector1, vector2;
	for (int i = 1; i <= size; i++)
		vector1.push_front(*PersonRecs[i]);

	std::cout << "Before assignment:" << std::endl;
	std::cout << "Vector 1:\n";
	std::cout << vector1;
	std::cout << "Vector 2:\n";
	std::cout << vector2;

	vector2 = vector1;
	std::cout << "After assignment:" << std::endl;
	std::cout << "Vector 1:\n";
	std::cout << vector1;
	std::cout << "Vector 2:\n";
	std::cout << vector2;

	std::cout << std::endl;
}

void TestAssignment2(void)
{
	std::cout << "TestAssignment2..." << std::endl;
	int size = 10;
	CS170::Vector<Person> vector1, vector2, vector3;
	for (int i = 1; i <= size; i++)
		vector1.push_front(*PersonRecs[i]);

	std::cout << "Before assignment:" << std::endl;
	std::cout << "Vector 1:\n";
	std::cout << vector1;
	std::cout << "Vector 2:\n";
	std::cout << vector2;
	std::cout << "Vector 3:\n";
	std::cout << vector3;

	vector3 = vector2 = vector1;
	std::cout << "After assignment:" << std::endl;
	std::cout << "Vector 1:\n";
	std::cout << vector1;
	std::cout << "Vector 2:\n";
	std::cout << vector2;
	std::cout << "Vector 3:\n";
	std::cout << vector3;

	vector1 = vector1;
	std::cout << "After self assignment:" << std::endl;
	std::cout << "Vector 1:\n";
	std::cout << vector1;

	std::cout << std::endl;
}

void TestAddition1(void)
{
	std::cout << "TestAddition1..." << std::endl;

	int size = 5;
	CS170::Vector<Person> vector1, vector2;
	for (int i = 1; i <= size; i++)
	{
		vector1.push_front(*PersonRecs[i]);
		vector2.push_front(*PersonRecs[i + 10]);
	}

	std::cout << "Before addition:" << std::endl;
	std::cout << "Vector 1:\n";
	std::cout << vector1;
	std::cout << "Vector 2:\n";
	std::cout << vector2;

	CS170::Vector<Person> vector3;
	vector3 = vector1 + vector2;
	std::cout << "After addition:" << std::endl;
	std::cout << "Vector 1:\n";
	std::cout << vector1;
	std::cout << "Vector 2:\n";
	std::cout << vector2;
	std::cout << "Vector 3:\n";
	std::cout << vector3;
	std::cout << std::endl;
}

void TestAddition2(void)
{
	std::cout << "TestAddition2..." << std::endl;

	int size = 5;
	CS170::Vector<Person> vector1, vector2;
	for (int i = 1; i <= size; i++)
	{
		vector1.push_front(*PersonRecs[i]);
		vector2.push_front(*PersonRecs[i + 10]);
	}

	std::cout << "Before addition:" << std::endl;
	std::cout << "Vector 1:\n";
	std::cout << vector1;
	std::cout << "Vector 2:\n";
	std::cout << vector2;

	const CS170::Vector<Person> vector3(vector1 + vector2);
	std::cout << "Vector 3:\n";
	std::cout << vector3;

	CS170::Vector<Person> vector4;
	vector4 = vector1 + vector2 + vector3;
	std::cout << "After addition:" << std::endl;
	std::cout << "Vector 4:\n";
	std::cout << vector4;
	std::cout << "Items in the vector: " << vector4.size() << std::endl;
	std::cout << std::endl;
}

void TestAddAssign1(void)
{
	std::cout << "TestAddAssign1..." << std::endl;

	int size = 5;
	CS170::Vector<Person> vector1, vector2;
	for (int i = 1; i <= size; i++)
	{
		vector1.push_front(*PersonRecs[i]);
		vector2.push_front(*PersonRecs[i + 5]);
	}

	std::cout << "Before addition:" << std::endl;
	std::cout << "Vector 1:\n";
	std::cout << vector1;
	std::cout << "Vector 2:\n";
	std::cout << vector2;

	vector1 += vector2;
	std::cout << "After addition:" << std::endl;
	std::cout << "Vector 1:\n";
	std::cout << vector1;
	std::cout << "Vector 2:\n";
	std::cout << vector2;
	std::cout << "Items in the vector: " << vector1.size() << std::endl;
	std::cout << std::endl;
}

void TestAddAssign2(void)
{
	std::cout << "TestAddAssign2..." << std::endl;

	int size = 5;
	CS170::Vector<Person> vector1, vector2;
	for (int i = 1; i <= size; i++)
		vector1.push_front(*PersonRecs[i]);

	std::cout << "Before addition:" << std::endl;
	std::cout << "Vector 1:\n";
	std::cout << vector1;
	std::cout << "Vector 2:\n";
	std::cout << vector2;

	vector1 += vector2;
	std::cout << "After addition:" << std::endl;
	std::cout << "Vector 1:\n";
	std::cout << vector1;
	std::cout << "Vector 2:\n";
	std::cout << vector2;
	std::cout << "Items in the vector: " << vector1.size() << std::endl;
	std::cout << std::endl;
}

void TestAddAssign3(void)
{
	std::cout << "TestAddAssign3..." << std::endl;

	int size = 5;
	CS170::Vector<Person> vector1, vector2;
	for (int i = 1; i <= size; i++)
		vector1.push_front(*PersonRecs[i]);

	std::cout << "Before addition:" << std::endl;
	std::cout << "Vector 1:\n";
	std::cout << vector1;
	std::cout << "Vector 2:\n";
	std::cout << vector2;

	vector2 += vector1;
	std::cout << "After addition:" << std::endl;
	std::cout << "Vector 1:\n";
	std::cout << vector1;
	std::cout << "Vector 2:\n";
	std::cout << vector2;
	std::cout << "Items in the vector: " << vector1.size() << std::endl;
	std::cout << std::endl;
}

void TestAddAssign4(void)
{
	std::cout << "TestAddAssign4..." << std::endl;

	int size = 5;
	CS170::Vector<Person> vector1, vector2, vector3;
	for (int i = 1; i <= size; i++)
	{
		vector1.push_front(*PersonRecs[i]);
		vector2.push_front(*PersonRecs[i + 8]);
		vector3.push_front(*PersonRecs[i + 15]);
	}

	std::cout << "Before addition:" << std::endl;
	std::cout << "Vector 1:\n";
	std::cout << vector1;
	std::cout << "Vector 2:\n";
	std::cout << vector2;
	std::cout << "Vector 3:\n";
	std::cout << vector3;

	vector1 += vector2 += vector3;
	std::cout << "After addition:" << std::endl;
	std::cout << "Vector 1:\n";
	std::cout << vector1;
	std::cout << "Vector 2:\n";
	std::cout << vector2;
	std::cout << "Vector 3:\n";
	std::cout << vector3;
	std::cout << "Items in the vector: " << vector1.size() << std::endl;
	std::cout << std::endl;
}

void TestSubscript1(void)
{
	std::cout << "TestSubscript1..." << std::endl;

	int size = 10;
	CS170::Vector<Person> vector1;
	for (int i = 1; i <= size; i++)
		vector1.push_back(*PersonRecs[i]);

	std::cout << "vector[0] = " << vector1[0];
	std::cout << "vector[5] = " << vector1[5];
	std::cout << "vector[9] = " << vector1[9];
	std::cout << std::endl;
}

void TestSubscript2(void)
{
	std::cout << "TestSubscript2..." << std::endl;

	int size = 10;
	CS170::Vector<Person> vector1;
	for (int i = 1; i <= size; i++)
		vector1.push_back(*PersonRecs[i]);

	std::cout << "Original vector:\n";
	std::cout << vector1;

	vector1[0] = *PersonRecs[12];
	vector1[5] = *PersonRecs[15];
	vector1[9] = *PersonRecs[19];
	vector1[7] = vector1[2];

	std::cout << "Modified vector:\n";
	std::cout << vector1;
}

int main(int argc, char **argv)
{
	int test_num = 0;
	if (argc > 1)
		test_num = std::atoi(argv[1]);

	typedef void(*Test)(void);
	Test Tests[] =
	{
		TestPushFront,		// Test 1
		TestPushBack,		// Test 2
		TestPushFrontBack,	// Test 3
		TestPopFront,		// Test 4
		TestArray1,			// Test 5
		TestArray2,			// Test 6
		TestCopyConstructor1,	// Test 7
		TestCopyConstructor2,	// Test 8
		TestAssignment1,	// Test 9
		TestAssignment2,	// Test 10
		TestAddAssign1,		// Test 11
		TestAddAssign2,		// Test 12
		TestAddAssign3,		// Test 13
		TestAddAssign4,		// Test 14
		TestSubscript1,		// Test 15
		TestSubscript2,		// Test 16
		TestAddition1,		// Test 17
		TestAddition2,		// Test 18
	};

	FillPersonRecs();

	int num = sizeof(Tests) / sizeof(*Tests);
	if (test_num == 0)
	{
		for (int i = 0; i < num; i++)
		{
			try { Tests[i](); }
			catch (...) { std::cout << "***Test " << i + 1 << " revealed something bad in the Vector class" << std::endl; }
			std::cout << "============================================" << std::endl;
		}
	}
	else if (test_num > 0 && test_num <= num)
	{
		try { Tests[test_num - 1](); }
		catch (...) { std::cout << "***Test " << test_num << " revealed something bad in the Vector class" << std::endl; }
		std::cout << "============================================" << std::endl;
	}

	FreePersonRecs();

	return 0;
}
