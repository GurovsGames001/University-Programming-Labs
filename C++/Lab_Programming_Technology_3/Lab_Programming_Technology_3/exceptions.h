#ifndef _EXCEPTIONS_H
#define _EXCEPTIONS_H
#include <exception>

class ErrorOpenFile : public std::exception
{
public:
	ErrorOpenFile() : reason_("ERROR: �� ������� ������� ������ ����") {};
	const char* what() const { return reason_; };
private:
	const char* reason_;
};

class ErrorInvalidCommand : public std::exception
{
public:
	ErrorInvalidCommand() : reason_("INVALID COMMAND") {};
	const char* what() const { return reason_; };
private:
	const char* reason_;
};

class ErrorVectorIsEmpty : public std::exception
{
public:
	ErrorVectorIsEmpty() : reason_("ERROR: ��� ���� ������� ���������� ������� ���� �� ����� ������") {};
	const char* what() const { return reason_; };
private:
	const char* reason_;
};

#endif