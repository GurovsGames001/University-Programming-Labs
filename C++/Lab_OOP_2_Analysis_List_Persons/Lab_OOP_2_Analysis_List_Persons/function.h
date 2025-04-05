#include "Person.h"

// ����������
template <typename Lines>
void sortPersons(Person<Lines>** array, const int n)
{
	for (int i = 0; i < n; i++)
	{
		for (int j = i; j < n - 1; j++)
		{
			if (*array[i] > *array[j + 1])
			{
				Person<Lines>* temp = array[i];
				array[i] = array[j + 1];
				array[j + 1] = temp;
			}
		}
	}
}

// ������� �������� ��������� ���
template <typename Lines>
int countDifferentName(Person<Lines>** array, const int n)
{
	int nDifferentName = 1;
	int iTempName = 0;

	for (int i = 1; i < n; i++)
	{
		if (array[iTempName]->getName() != array[i]->getName())
		{
			nDifferentName++;
			iTempName = i;
		}
	}

	return nDifferentName;
}

// ������� ����������� ������� ���������� ��� � ������, ���������� � ���� ���
template <typename Lines>
bool isIdenticalName(Person<Lines>** array, const int n)
{
	bool isTrue = false;
	int iTempName = 0;
	int iTempYear = 0;

	for (int i = 1; i < n; i++)
	{
		if (array[iTempYear]->getYearBirth() != array[i]->getYearBirth())
		{
			iTempYear = i;
		}
		else
		{
			if (array[iTempName]->getName() == array[i]->getName())
			{
				isTrue = true;
				break;
			}
		}
		if (array[iTempName]->getName() != array[i]->getName())
		{
			iTempName = i;
		}
	}

	return isTrue;
}

// ������� ������ ������� � ����
template <typename Lines>
void outArray(Person<Lines>** array, const int n, std::ofstream& fout)
{
	for (int i = 0; i < n; i++)
	{
		fout << *array[i] << '\n';
	}
	fout << '\n';
}