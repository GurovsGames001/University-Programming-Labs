#include <iostream>
#include <fstream>
#include <string>
#include "String.h"
#include "Person.h"
#include "function.h"
#include "friendFunctionPatternIsCorrectPerson.h"

static int g_numberStringInFile = 2; // ����� ������ �� ������� �����
int getNumberStringInFile() // ������� ��������� ������ ������
{
	return g_numberStringInFile;
}

const size_t LENGTH_IN_STRING = 45; // ������������ ������ ������� ������ (37) + ������� ����� �� ������ ������ �������� ����� �������

const std::string ERROR_FILE_NOT_OPEN = "������: ��� �������� ����� ��������� ������";
const std::string ERROR_NOT_NUMBER = "������: ����� ������� � ����� ������ ���� ������������ ����� ������";
const std::string ERROR_NUMBER_ZERO = "������: ����� ������� � ����� ������ ���� ������������ ������������� ������";
const std::string ERROR_LARGE_NUMBER = "������: ����� ������� � ����� ������ ����������";
const std::string ERROR_SMALL_NUMBER = "������: ����� ������� � ����� ������ ����������";

int main()
{
	setlocale(LC_ALL, "rus");

	try
	{
		// ��������� ������ ��� ����� � ������
		std::ifstream fin;
		std::cout << "������� ��� �������� �����: ";
		std::string inFileName;
		std::cin >> inFileName; // list_of_persons.txt
		fin.open(inFileName);
		if (!fin)
		{
			throw ERROR_FILE_NOT_OPEN;
		}
		std::cout << "\n";

		std::ofstream fout;
		std::cout << "������� ��� ��������� �����: ";
		std::string outFileName;
		std::cin >> outFileName; // out_list_of_persons.txt
		fout.open(outFileName);
		if (!fout)
		{
			throw ERROR_FILE_NOT_OPEN;
		}
		std::cout << "\n";

		// ���� ���������� �� �����
		int n = 0;
		fin >> n;

		if (!fin)
		{
			throw ERROR_NOT_NUMBER;
		}
		if (n < 0)
		{
			throw ERROR_NUMBER_ZERO;
		}

		Person<String>* arrayMyString = new Person<String>[n];
		Person<std::string>* arrayStdString = new Person<std::string>[n];
		Person<String>** arrayPointerMyString = new Person<String>*[n];
		Person<std::string>** arrayPointerStdString = new Person<std::string>*[n];

		fin.ignore(n, '\n');

		char* tempStr = new char[LENGTH_IN_STRING];
		for (int i = 0; i < n; i++)
		{
			if (fin.eof())
			{
				throw ERROR_LARGE_NUMBER;
			}

			fin.getline(tempStr, LENGTH_IN_STRING, '\n');

			arrayMyString[i] = tempStr;
			arrayPointerMyString[i] = &arrayMyString[i];

			arrayStdString[i] = tempStr;
			arrayPointerStdString[i] = &arrayStdString[i];

			g_numberStringInFile++; // ����� ������ � �����
		}

		if (!(fin.eof()))
		{
			throw ERROR_SMALL_NUMBER;
		}

		fin.close();
		delete[] tempStr;

		// ���������� � ���������� ������ �������
		sortPersons(arrayPointerMyString, n);
		sortPersons(arrayPointerStdString, n);

		int nDifferentNameMyString = 0;
		int nDifferentNameStdString = 0;
		nDifferentNameMyString = countDifferentName(arrayPointerMyString, n);
		nDifferentNameStdString = countDifferentName(arrayPointerStdString, n);

		std::string isIdenticalNameMyString = "";
		std::string isIdenticalStdString = "";
		isIdenticalNameMyString = (isIdenticalName(arrayPointerMyString, n)) ? "��" : "���";
		isIdenticalStdString = (isIdenticalName(arrayPointerStdString, n)) ? "��" : "���";

		// ����� ���������� � ����
		fout << "�����: String" << '\n';
		outArray(arrayPointerMyString, n, fout);
		fout << "�����: std::string" << '\n';
		outArray(arrayPointerStdString, n, fout);

		std::cout << "���������� ��������� ��� � �����:\n"
					<< "   1) String: " << nDifferentNameMyString << '\n'
					<< "   2) std::string: " << nDifferentNameStdString << '\n';
		std::cout << "\n";
		std::cout << "������� ���������� ��� � ������, ���������� � ���� ���:\n"
					<< "   1) String: " << isIdenticalNameMyString << '\n'
					<< "   2) std::string: " << isIdenticalStdString << '\n';

		fout.close();

		// ������������ ������
		delete[] arrayMyString;
		delete[] arrayPointerMyString;
		delete[] arrayStdString;
		delete[] arrayPointerStdString;
	}

	catch (const std::string& error)
	{
		std::cerr << error << '\n';
		return -1;
	}

	catch (std::bad_alloc& ba)
	{
		std::cout << ba.what() << '\n';
		return -1;
	}

	return 0;
}