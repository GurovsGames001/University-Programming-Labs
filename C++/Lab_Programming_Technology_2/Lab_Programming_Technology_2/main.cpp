#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <iterator>
#include <algorithm>
#include "DataStruct.h"
#include "overloadedInputOutput.h"

int main()
{
	setlocale(LC_ALL, "rus");

	std::vector<DataStruct> data;

	std::ifstream fin;
	std::string inFileName = "input_data.txt";
	fin.open(inFileName);

	while (!fin.eof())
	{
		if (fin.good())
		{
			std::copy(std::istream_iterator<DataStruct>(fin), std::istream_iterator<DataStruct>(), std::back_inserter(data));
		}
		else
		{
			fin.clear();
			fin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
	}

	fin.close();

	std::sort(std::begin(data), std::end(data), DataStructComparator());

	std::cout << "Data:\n";
	std::copy(std::begin(data), std::end(data), std::ostream_iterator<DataStruct>(std::cout, "\n"));

	return 0;
}