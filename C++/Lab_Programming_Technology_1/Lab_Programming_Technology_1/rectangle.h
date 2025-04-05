#ifndef _RECTANGLE
#define _RECTANGLE
#include "shape.h"

class Rectangle : public Shape
{
public:
	Rectangle() {};
	Rectangle(double x1, double y1, double x2, double y2);
	~Rectangle() {};

	double getArea() const override; // ���������� �������
	rectangle_t getFrameRect() const override; // ��������� ��������������� ��������������
	void move(point_t newPos) override; // ����������� ������ ������ � ���������� �����
	void move(double k1, double k2) override; // ����������� ������ ������ � ���� �������� �� ���� ������� � �������
	void scale(double k) override; // ���������� ���������������
	void print() const override; // ������ ������ � ������

private:
	point_t leftPoint_;
	point_t rightPoint_;
	point_t centre_;

	void isCorrect() const override; // �������� ������������ ��������������
};

#endif