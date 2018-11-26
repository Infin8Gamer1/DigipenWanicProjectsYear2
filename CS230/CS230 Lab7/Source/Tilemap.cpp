#include "stdafx.h"
#include "Tilemap.h"
#include <fstream>
#include <iostream>
#include <string>

Tilemap::Tilemap(unsigned _numColumns, unsigned _numRows, int ** _data)
{
	// Dimensions of the map
	numColumns = _numColumns;
	numRows = _numRows;

	// The map data (a 2D array)
	data = _data;
}

Tilemap::~Tilemap()
{
	// Deleting the 2D array
	// delete in the opposite order of creation
	for (int r = 0; r < numRows; ++r)
	{
		delete[] data[r]; // delete each allocated row with array delete
		data[r] = nullptr; // safely set to nullptr
	}
	// Use array delete, since array new was used in allocation
	delete[] data;
	data = nullptr; // safely set to nullptr.
}

unsigned Tilemap::GetWidth() const
{
	return numColumns;
}

unsigned Tilemap::GetHeight() const
{
	return numRows;
}

int Tilemap::GetCellValue(unsigned column, unsigned row) const
{
	//if given row or column is outside of the array then just return -1
	if ((column >= numColumns || column < 0) || (row >= numRows || row < 0)) {
		return -1;
	}
	//other wise return the correct value
	return data[column][row];
}

Tilemap * Tilemap::CreateTilemapFromFile(const std::string & filename)
{
	std::ifstream infile(filename);
	if (!infile.is_open()) 
	{ 
		std::cout << "Can't open file '" + filename + "'." << std::endl;
		return nullptr;
	}
	
	int rows = -1;
	int columns = -1;

	ReadIntegerVariable(infile, "width", rows);
	ReadIntegerVariable(infile, "height", columns);

	Tilemap* output = new Tilemap(columns, rows, ReadArrayVariable(infile, "data", columns, rows));

	infile.close();
	
	return output;
}

bool Tilemap::ReadIntegerVariable(std::ifstream & file, const std::string & name, int & variable)
{
	std::string str;
	//read name
	file >> str;
	//if correct name then return true and put stuff in variable
	if (str == name) {
		file >> variable;
		return true;
	}
	//we didn't find it and we are failures!
	return false;
}

int ** Tilemap::ReadArrayVariable(std::ifstream & file, const std::string & name, unsigned columns, unsigned rows)
{

	std::string str;
	//read name
	file >> str;

	if (str != name) {
		return nullptr;
	}

	//make a new 2D int array
	int **output = new int *[rows];
	for (int r = 0; r < rows; ++r)
	{
		output[r] = new int[columns];
	}	//loop through each value in the 2D array	for (int r = 0; r < rows; r++)
	{
		for (int c = 0; c < columns; c++)
		{
			//read the next int
			int value;
			file >> value;
			//set that value in output
			output[r][c] = value;
		}
	}

	return output;
}
