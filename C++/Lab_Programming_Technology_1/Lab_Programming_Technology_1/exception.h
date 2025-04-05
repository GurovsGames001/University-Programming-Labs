#ifndef _EXCEPTION
#define _EXCEPTION
#include <exception>

class ErrorNoCorrectRectangle : public std::exception
{
public:
	ErrorNoCorrectRectangle(): reason_("ERROR: Прямоугольник задан неправильно") {}
	const char* what() const { return reason_; }
private:
	const char* reason_;
};

class ErrorNoCorrectCircle : public std::exception
{
public:
	ErrorNoCorrectCircle() : reason_("ERROR: Круг задан неправильно") {}
	const char* what() const { return reason_; }
private:
	const char* reason_;
};

class ErrorNoCorrectParallelogram : public std::exception
{
public:
	ErrorNoCorrectParallelogram() : reason_("ERROR: Параллелограмм задан неправильно") {}
	const char* what() const { return reason_; }
private:
	const char* reason_;
};

#endif