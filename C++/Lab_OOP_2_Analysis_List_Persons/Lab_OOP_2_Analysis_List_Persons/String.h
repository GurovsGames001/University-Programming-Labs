#ifndef STRING_H
#define STRING_H
#include <iostream>
#include <fstream>

class String
{
public:
	String() : size_(0), capacity_(16), pointer_(new char(16))
	{
		*pointer_ = '\0';
	}
	String(const char* str);
	String(const String& object) : size_(object.size_), capacity_(object.capacity_)
	{
		pointer_ = new char[capacity_];
		copy(object.pointer_);
	}
	String(String&& object) noexcept : size_(object.size_), capacity_(object.capacity_), pointer_(object.pointer_)
	{
		object.size_ = 0;
		object.capacity_ = 0;
		object.pointer_ = nullptr;
	}
	~String()
	{
		delete[] pointer_;
	}

	size_t getSize() const;
	int compare(const String& str) const;

	String& operator=(const char* str);
	String& operator=(String&& str) noexcept;
	String& operator=(String& str) noexcept;
	char& operator[](size_t pos);
	const char& operator[](size_t pos) const;
	bool operator<(const String& str) const;
	bool operator>(const String& str) const;
	bool operator==(const String& str) const;
	bool operator!=(const String& str) const;

	friend std::ostream& operator<<(std::ostream& out, const String& str);

private:
	size_t size_;
	size_t capacity_;
	char* pointer_;

	size_t length(const char* str);
	void copy(const char* str);
	void swap(String& str);
};

#endif