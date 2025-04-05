#include "String.h"
#include <utility>
#include <string>

const std::string ERROR_INDEX = "Ошибка: индекс элемента не соответствует размеру строки";

// Конструкторы

String::String(const char* str)
{
	size_ = length(str);
	capacity_ = size_ + 1;
	pointer_ = new char[capacity_];
	this->copy(str);
}

// Методы из private

size_t String::length(const char* str)
{
	size_t size = 0;
	for (size = 0; str[size] != '\0'; size++)
	{}

	return size;
}

void String::copy(const char* str)
{
	size_t i = 0;
	for (i = 0; str[i] != '\0'; i++)
	{
		pointer_[i] = str[i];
	}

	pointer_[i] = str[i];
}

void String::swap(String& str)
{
	std::swap(size_, str.size_);
	std::swap(capacity_, str.capacity_);
	std::swap(pointer_, str.pointer_);
}

// Методы из public

size_t String::getSize() const
{
	return size_;
}

int String::compare(const String& str) const
{
	int pos = 0;
	int result = 0;
	for (pos = 0; ((pos < size_) && (pos < str.size_)); pos++)
	{
		if (((*this)[pos]) < str[pos])
		{
			result = -1;
			break;
		}
		else if (((*this)[pos]) > str[pos])
		{
			result = 1;
			break;
		}
	}
	if ((result == 0) && (size_ != str.size_))
	{
		result = (size_ < str.size_) ? -1 : 1;
	}

	return result;
}

// Перегруженные операторы

String& String::operator=(const char* str)
{
	size_t sizeStr = length(str);
	if (sizeStr <= size_)
	{
		size_ = sizeStr;
		this->copy(str);
	}
	else
	{
		size_ = sizeStr;
		capacity_ = size_ + 1;
		pointer_ = new char[capacity_];
		this->copy(str);
	}

	return *this;
}

String& String::operator=(String&& str) noexcept
{
	if (this != &str)
	{
		swap(str);
	}

	return *this;
}

String& String::operator=(String& str) noexcept
{
	if (this != &str)
	{
		String temp(str);
		swap(temp);
	}

	return *this;
}

char& String::operator[](const size_t pos)
{
	if (!((pos >= 0) && (pos <= size_ - 1)))
	{
		throw ERROR_INDEX;
	}

	return pointer_[pos];
}

const char& String::operator[](size_t pos) const
{
	if (!((pos >= 0) && (pos <= size_ - 1)))
	{
		throw ERROR_INDEX;
	}

	return pointer_[pos];
}

bool String::operator<(const String& str) const
{
	return (*this).compare(str) < 0;
}

bool String::operator>(const String& str) const
{
	return (*this).compare(str) > 0;
}

bool String::operator==(const String& str) const
{
	return (*this).compare(str) == 0;
}

bool String::operator!=(const String& str) const
{
	return (!((*this) == str));
}

std::ostream& operator<<(std::ostream &out, const String& str)
{
	return (out << str.pointer_);
}