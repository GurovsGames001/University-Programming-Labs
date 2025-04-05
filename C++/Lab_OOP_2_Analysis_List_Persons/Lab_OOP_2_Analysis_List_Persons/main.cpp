#include <iostream>
#include <fstream>
#include <string>
#include "String.h"
#include "Person.h"
#include "function.h"
#include "friendFunctionPatternIsCorrectPerson.h"

static int g_numberStringInFile = 2; // Номер строки во входном файле
int getNumberStringInFile() // Функция получения номера строки
{
	return g_numberStringInFile;
}

const size_t LENGTH_IN_STRING = 45; // Максимальный размер входной строки (37) + немного места на случай лишних пробелов между словами

const std::string ERROR_FILE_NOT_OPEN = "Ошибка: при открытии файла произошла ошибка";
const std::string ERROR_NOT_NUMBER = "Ошибка: число записей в файле должно быть представлено целым числом";
const std::string ERROR_NUMBER_ZERO = "Ошибка: число записей в файле должно быть представлено положительным числом";
const std::string ERROR_LARGE_NUMBER = "Ошибка: число записей в файле меньше указанного";
const std::string ERROR_SMALL_NUMBER = "Ошибка: число записей в файле больше указанного";

int main()
{
	setlocale(LC_ALL, "rus");

	try
	{
		// Получение файлов для ввода и вывода
		std::ifstream fin;
		std::cout << "Введите имя входного файла: ";
		std::string inFileName;
		std::cin >> inFileName; // list_of_persons.txt
		fin.open(inFileName);
		if (!fin)
		{
			throw ERROR_FILE_NOT_OPEN;
		}
		std::cout << "\n";

		std::ofstream fout;
		std::cout << "Введите имя выходного файла: ";
		std::string outFileName;
		std::cin >> outFileName; // out_list_of_persons.txt
		fout.open(outFileName);
		if (!fout)
		{
			throw ERROR_FILE_NOT_OPEN;
		}
		std::cout << "\n";

		// Ввод информации из файла
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

			g_numberStringInFile++; // номер строки в файле
		}

		if (!(fin.eof()))
		{
			throw ERROR_SMALL_NUMBER;
		}

		fin.close();
		delete[] tempStr;

		// Сортировка и применение других функций
		sortPersons(arrayPointerMyString, n);
		sortPersons(arrayPointerStdString, n);

		int nDifferentNameMyString = 0;
		int nDifferentNameStdString = 0;
		nDifferentNameMyString = countDifferentName(arrayPointerMyString, n);
		nDifferentNameStdString = countDifferentName(arrayPointerStdString, n);

		std::string isIdenticalNameMyString = "";
		std::string isIdenticalStdString = "";
		isIdenticalNameMyString = (isIdenticalName(arrayPointerMyString, n)) ? "Да" : "Нет";
		isIdenticalStdString = (isIdenticalName(arrayPointerStdString, n)) ? "Да" : "Нет";

		// Вывод информации в файл
		fout << "Класс: String" << '\n';
		outArray(arrayPointerMyString, n, fout);
		fout << "Класс: std::string" << '\n';
		outArray(arrayPointerStdString, n, fout);

		std::cout << "Количество различных имён в файле:\n"
					<< "   1) String: " << nDifferentNameMyString << '\n'
					<< "   2) std::string: " << nDifferentNameStdString << '\n';
		std::cout << "\n";
		std::cout << "Наличие одинаковых имён у персон, родившихся в один год:\n"
					<< "   1) String: " << isIdenticalNameMyString << '\n'
					<< "   2) std::string: " << isIdenticalStdString << '\n';

		fout.close();

		// Освобождение памяти
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