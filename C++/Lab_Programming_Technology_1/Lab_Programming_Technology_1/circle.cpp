#define _USE_MATH_DEFINES
#include "circle.h"
#include <cmath>
#include <iostream>

// ���������� �������
double Circle::getArea() const
{
	return M_PI * radius_ * radius_;
}

// ��������� ��������������� ��������������
rectangle_t Circle::getFrameRect() const
{
	rectangle_t temp;

	temp.width_ = 2 * radius_;
	temp.height_ = 2 * radius_;
	temp.pos_ = centre_;

	return temp;
}

// ����������� ������ ������ � ���������� �����
void Circle::move(point_t newPos)
{
	if ((newPos.x_ != centre_.x_) || (newPos.y_ != centre_.y_))
	{
		this->centre_ = newPos;
	}
}

// ����������� ������ ������ � ���� �������� �� ���� ������� � �������
void Circle::move(double k1, double k2)
{
	this->centre_.x_ += k1;
	this->centre_.y_ += k2;
}

// ���������� ���������������
void Circle::scale(double k)
{
	this->radius_ *= k;
}

// ������ ������ � ������
void Circle::print() const
{
	std::cout << "������: " << radius_
		<< " �����: (" << centre_.x_ << "; " << centre_.y_ << ")\n";
}

// �������� ������������ ��������������
void Circle::isCorrect() const
{
	if (radius_ <= 0)
	{
		throw ErrorNoCorrectCircle();
	}
}