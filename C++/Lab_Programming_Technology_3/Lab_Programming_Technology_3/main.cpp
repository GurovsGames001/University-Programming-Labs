#include <iostream>
#include <fstream>
#include <algorithm>
#include <functional>
#include <vector>
#include <string>
#include <sstream>
#include "structs.h"
#include "exceptions.h"
#include "overloadedInputOutput.h"
#include "functions.h"

inline void executeCommand(std::vector<Polygon>& data, const Command& command);
inline void printMenu();
inline bool isNumber(const std::string& str);

int main()
{
	setlocale(LC_ALL, "rus");

	try 
	{
		std::ifstream fin;
		std::string inFileName = "input_data.txt";
		fin.open(inFileName);
		if (!fin.is_open())
		{
			throw ErrorOpenFile();
		}

		std::vector<Polygon> polygons;
		std::string tempString;

		while (!fin.eof())
		{
			std::getline(fin, tempString);
			std::istringstream iss(tempString);

			std::copy(std::istream_iterator<Polygon>(iss), std::istream_iterator<Polygon>(), std::back_inserter(polygons));
		}

		printMenu();
		std::istream& in = std::cin;
		bool isExit = false;

		std::string inputString;
		while (!isExit)
		{
			std::cout << "\n������� �������: ";

			std::getline(in, inputString);
			std::istringstream iss(inputString);
			Command command;
			iss >> command;
			if (!iss.eof() || iss.fail())
			{
				std::cout << "INVALID COMMAND" << std::endl;
			}
			else if (command.command == "EXIT")
			{
				isExit = true;
			}
			else
			{
				executeCommand(polygons, command);
			}
		}
	}

	catch (const std::exception& error)
	{
		std::cout << error.what() << std::endl;
		return -1;
	}

	return 0;
}

inline void executeCommand(std::vector<Polygon>& polygons, const Command& command)
{
	if (command.command == "AREA")
	{
		if ((command.parameter != "EVEN") && (command.parameter != "ODD") && (command.parameter != "MEAN"))
		{
			if (!isNumber(command.parameter))
			{
				std::cout << "INVALID COMMAND" << std::endl;
			}
			else
			{
				executeArea(polygons, command.parameter);
			}
		}
		else
		{
			executeArea(polygons, command.parameter);
		}
	}
	else if (command.command == "MAX")
	{
		if ((command.parameter != "AREA") && (command.parameter != "VERTEXES"))
		{
			std::cout << "INVALID COMMAND" << std::endl;
		}
		else
		{
			executeMax(polygons, command.parameter);
		}
	}
	else if (command.command == "MIN")
	{
		if ((command.parameter != "AREA") && (command.parameter != "VERTEXES"))
		{
			std::cout << "INVALID COMMAND" << std::endl;
		}
		else
		{
			executeMin(polygons, command.parameter);
		}
	}
	else if (command.command == "COUNT")
	{
		if ((command.parameter != "EVEN") && (command.parameter != "ODD"))
		{
			if (!isNumber(command.parameter))
			{
				std::cout << "INVALID COMMAND" << std::endl;
			}
			else
			{
				executeCount(polygons, command.parameter);
			}
		}
		else
		{
			executeCount(polygons, command.parameter);
		}
	}
	else if (command.command == "MAXSEQ")
	{
		executeMaxseq(polygons, command.polygon);
	}
	else if (command.command == "ECHO")
	{
		executeEcho(polygons, command.polygon);
	}
	else
	{
		std::cout << "INVALID COMMAND" << std::endl;
	}
}

inline void printMenu()
{
	std::cout << "������ ������� � ����������:\n";
	std::cout << " 1) [AREA <EVEN|ODD>] - ������ ����� ������� ����� � �������� ����������� ������ � � ������\n" << "    (� ����������� �� ����������� ���������)\n";
	std::cout << " 2) [AREA <MEAN>] - ������ �������� �������� �����\n";
	std::cout << " 3) [AREA <num-of-vertexes>] - ������ ����� ������� ����� � �������� ����������� ������\n";
	std::cout << " 4) [MAX <AREA|VERTEXES>] - ������ ������������� �������� ������� ��� ���������� ������\n    (� ����������� �� ����������� ���������)\n";
	std::cout << " 5) [MIN <AREA|VERTEXES>] - ������ ������������ �������� ������� ��� ���������� ������\n    (� ����������� �� ����������� ���������)\n";
	std::cout << " 6) [COUNT <EVEN|ODD|num-of-Vertexes>] - ������� ���������� ����� � ��������, ������\n    � ���������� ����������� ������ (� ����������� �� ����������� ���������)\n";
	std::cout << " 7) [MAXSEQ <Polygon>] - ������� ������������� ���������� ������ ������ �����\n    ���������� ��������� � ����������\n";
	std::cout << " 8) [ECHO <Polygon>] - ��������� ������ ��������� ��������� � ��������� ������.\n    ������� ������� ���������� ����������� �����\n";
	std::cout << " 9) [EXIT] - ����� �� ���������\n";
}

inline bool isNumber(const std::string& str)
{
	bool isNumber = std::find_if(str.begin(), str.end(), [](char c) { return !std::isdigit(c); }) == str.end();
	return !str.empty() && isNumber;
}