#ifndef PERSON_H
#define PERSON_H
#include <iostream>
#include <fstream>

template <class Lines>
class Person
{
public:
	Person(): surname_(), name_(), yearBirth_() {}
	Person(const char* str);
	Person(const Person& object): surname_(object.surname_), name_(object.name_), yearBirth_(object.yearBirth_) {}
	~Person() {}

	Lines getSurname();
	Lines getName();
	Lines getYearBirth();

	Person& operator=(char* str);
	bool operator<(const Person& person) const;
	bool operator>(const Person& person) const;
	bool operator==(const Person& person) const;
	
	friend bool isPerson(const Person<Lines>& ob);

	template <class Lines> friend std::ostream& operator<<(std::ostream& out, const Person<Lines>& person);

private:
	Lines surname_;
	Lines name_;
	Lines yearBirth_;

	size_t lengthToSymbol(const char* str, int pos, char symbol);
	char* splitStr(const char* str, int& pos, char symbol);
	void swap(Person& object);
};

// Конструкторы

template <class Lines>
Person<Lines>::Person(const char* str)
{
	int pos = 0;

	surname_ = splitStr(str, pos, ' ');
	name_ = splitStr(str, pos, ' ');
	yearBirth_ = splitStr(str, pos, ' ');

	isPerson(*this);
}

// Методы из public

template <class Lines>
Lines Person<Lines>::getSurname()
{
	return surname_;
}

template <class Lines>
Lines Person<Lines>::getName()
{
	return name_;
}

template <class Lines>
Lines Person<Lines>::getYearBirth()
{
	return yearBirth_;
}

// Методы из private

template <class Lines>
size_t Person<Lines>::lengthToSymbol(const char* str, int pos, char symbol)
{
	size_t i = pos;
	for (i = pos; (str[i] != symbol) && (str[i] != '\0'); i++);

	return i - pos;
}

template <class Lines>
char* Person<Lines>::splitStr(const char* str, int& pos, char symbol)
{
	int newPos = 0;
	size_t sizeStr = lengthToSymbol(str, pos, symbol);
	char* newStr = new char[sizeStr + 1];

	for (newPos = 0; newPos < sizeStr; newPos++)
	{
		newStr[newPos] = str[pos];
		pos++;
	}

	newStr[newPos] = '\0';

	if (str[pos] == symbol)
	{
		while (str[pos] == symbol)
		{
			pos++;
		}
	}

	return newStr;
}

template <class Lines>
void Person<Lines>::swap(Person<Lines>& object)
{
	std::swap(surname_, object.surname_);
	std::swap(name_, object.name_);
	std::swap(yearBirth_, object.yearBirth_);
}

// Перегруженные операторы

template <class Lines>
Person<Lines>& Person<Lines>::operator=(char* str)
{
	Person<Lines> newPerson = str;
	this->swap(newPerson);

	return *this;
}

template <class Lines>
bool Person<Lines>::operator<(const Person& person) const
{
	bool result = (*this).name_ < person.name_;
	if ((*this).name_ == person.name_)
	{
		result = (*this).yearBirth_ < person.yearBirth_;
		if ((*this).yearBirth_ == person.yearBirth_)
		{
			result = (*this).surname_ < person.surname_;
		}
	}

	return result;
}

template <class Lines>
bool Person<Lines>::operator>(const Person<Lines>& person) const
{
	bool result = (*this).name_ > person.name_;
	if ((*this).name_ == person.name_)
	{
		result = (*this).yearBirth_ > person.yearBirth_;
		if ((*this).yearBirth_ == person.yearBirth_)
		{
			result = (*this).surname_ > person.surname_;
		}
	}

	return result;
}

template <class Lines>
bool Person<Lines>::operator==(const Person<Lines>& person) const
{
	return (!((*this) > person) || ((*this) < person));
}

template <class Lines>
std::ostream& operator<<(std::ostream& out, const Person<Lines>& person)
{
	return (out << person.surname_ << " " << person.name_ << " " << person.yearBirth_);
}

#endif