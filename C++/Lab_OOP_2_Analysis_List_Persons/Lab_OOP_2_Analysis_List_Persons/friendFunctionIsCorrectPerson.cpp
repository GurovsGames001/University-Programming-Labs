#include "Person.h"
#include "String.h"
#include "friendFunctionPatternIsCorrectPerson.h"
#include <string>

const std::string NUMBER_STRING = "C����� ����� ";
const std::string ERROR_NOT_SURNAME = ". ������: ������� ������� �������";
const std::string ERROR_NOT_NAME = ". ������: ��� ������� �������";
const std::string ERROR_NOT_YEAR_BIRTH = ". ������: ��� �������� ����� �������";

bool isSurname(const String& surname);
bool isSurname(const std::string& surname);
bool isName(const String& name);
bool isName(const std::string& name);
bool isYearBirth(const String& yearBirth);
bool isYearBirth(const std::string& yearBirth);

bool isPerson(const Person<String>& ob)
{
	if (!(isSurname(ob.surname_)))
	{
		throw NUMBER_STRING + std::to_string(getNumberStringInFile()) + ERROR_NOT_SURNAME;
	}
	if (!(isName(ob.name_)))
	{
		throw NUMBER_STRING + std::to_string(getNumberStringInFile()) + ERROR_NOT_NAME;
	}
	if (!(isYearBirth(ob.yearBirth_)))
	{
		throw NUMBER_STRING + std::to_string(getNumberStringInFile()) + ERROR_NOT_YEAR_BIRTH;
	}

	return true;
}

bool isPerson(const Person<std::string>& ob)
{
	if (!(isSurname(ob.surname_)))
	{
		throw NUMBER_STRING + std::to_string(getNumberStringInFile()) + ERROR_NOT_SURNAME;
	}
	if (!(isName(ob.name_)))
	{
		throw NUMBER_STRING + std::to_string(getNumberStringInFile()) + ERROR_NOT_NAME;
	}
	if (!(isYearBirth(ob.yearBirth_)))
	{
		throw NUMBER_STRING + std::to_string(getNumberStringInFile()) + ERROR_NOT_YEAR_BIRTH;
	}

	return true;
}

// �������� ������������ �������
bool isSurname(const String& surname)
{
	size_t sizeStr = surname.getSize();

	return isCorrectSurname(surname, sizeStr);
}

bool isSurname(const std::string& surname)
{
	size_t sizeStr = surname.length();

	return isCorrectSurname(surname, sizeStr);
}

// �������� ������������ �����
bool isName(const String& name)
{
	size_t sizeStr = name.getSize();

	return isCorrectName(name, sizeStr);
}

bool isName(const std::string& name)
{
	size_t sizeStr = name.length();

	return isCorrectName(name, sizeStr);
}

// �������� ������������ ���� ��������
bool isYearBirth(const String& yearBirth)
{
	size_t sizeStr = yearBirth.getSize();

	return isCorrectYearBirth(yearBirth, sizeStr);
}

bool isYearBirth(const std::string& yearBirth)
{
	size_t sizeStr = yearBirth.length();

	return isCorrectYearBirth(yearBirth, sizeStr);
}