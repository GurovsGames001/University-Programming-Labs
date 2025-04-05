#ifndef _CIRCLE
#define _CIRCLE
#include "shape.h"

class Circle : public Shape
{
public:
	Circle() : radius_(0) {};
	Circle(double x, double y, double radius) : centre_(x, y), radius_(radius) { isCorrect(); };
	~Circle() {};

	double getArea() const override; // ���������� �������
	rectangle_t getFrameRect() const override; // ��������� ��������������� ��������������
	void move(point_t newPos) override; // ����������� ������ ������ � ���������� �����
	void move(double k1, double k2) override; // ����������� ������ ������ � ���� �������� �� ���� ������� � �������
	void scale(double k) override; // ���������� ���������������
	void print() const override; // ������ ������ � ������

private:
	point_t centre_;
	double radius_;

	void isCorrect() const override; // �������� ������������ ��������������
};

#endif