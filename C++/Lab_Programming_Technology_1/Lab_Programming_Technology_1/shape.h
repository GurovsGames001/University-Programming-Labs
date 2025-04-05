#ifndef _SHAPE
#define _SHAPE
#include "base-types.h"
#include "exception.h"

class Shape
{
public:
	virtual ~Shape() {};

	virtual double getArea() const = 0; // ���������� �������
	virtual rectangle_t getFrameRect() const = 0; // ��������� ��������������� ��������������
	virtual void move(point_t newPos) = 0; // ����������� ������ ������ � ���������� �����
	virtual void move(double k1, double k2) = 0; // ����������� ������ ������ � ���� �������� �� ���� ������� � �������
	virtual void scale(double k) = 0; // ���������� ���������������
	virtual void print() const = 0; // ������ ������ � ������

private:
	point_t centre_;

	virtual void isCorrect() const = 0; // �������� ������������ �������� ������
};

#endif