#ifndef _PARALLELOGRAM
#define _PARALLELOGRAM
#include "shape.h"

class Parallelogram : public Shape
{
public:
	Parallelogram() {};
	Parallelogram(double x1, double y1, double x2, double y2, double x3, double y3);
	~Parallelogram() {};

	double getArea() const override; // ���������� �������
	rectangle_t getFrameRect() const override; // ��������� ��������������� ��������������
	void move(point_t newPos) override; // ����������� ������ ������ � ���������� �����
	void move(double k1, double k2) override; // ����������� ������ ������ � ���� �������� �� ���� ������� � �������
	void scale(double k) override; // ���������� ���������������
	void print() const override; // ������ ������ � ������

private:
	point_t vertex1_;
	point_t vertex2_;
	point_t vertex3_;
	point_t centre_;

	void isCorrect() const override; // �������� ������������ ��������������
};

#endif