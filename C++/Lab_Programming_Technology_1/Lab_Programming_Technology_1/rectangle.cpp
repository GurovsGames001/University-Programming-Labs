#include "rectangle.h"
#include <iostream>

// ����������������� �����������
Rectangle::Rectangle(double x1, double y1, double x2, double y2) : leftPoint_(x1, y1), rightPoint_(x2, y2)
{
	if (x1 > x2)
	{
		std::swap(leftPoint_, rightPoint_);
	}

	centre_.x_ = x1 + (x2 - x1) / 2;
	centre_.y_ = y1 + (y2 - y1) / 2;

	isCorrect();
}

// ���������� �������
double Rectangle::getArea() const
{
	double width = 0;
	double height = 0;

	width = rightPoint_.x_ - leftPoint_.x_;
	height = rightPoint_.y_ - leftPoint_.y_;

	return width * height;
}

// ��������� ��������������� ��������������
rectangle_t Rectangle::getFrameRect() const
{
	rectangle_t temp;

	temp.width_ = rightPoint_.x_ - leftPoint_.x_;
	temp.height_ = rightPoint_.y_ - leftPoint_.y_;
	temp.pos_ = centre_;

	return temp;
}

// ����������� ������ ������ � ���������� �����
void Rectangle::move(point_t newPos)
{
	if ((newPos.x_ != centre_.x_) || (newPos.y_ != centre_.y_))
	{
		double k1 = 0;
		double k2 = 0;
		k1 = newPos.x_ - centre_.x_;
		k2 = newPos.y_ - centre_.y_;

		this->centre_ = newPos;

		this->leftPoint_.x_ += k1;
		this->leftPoint_.y_ += k2;
		this->rightPoint_.x_ += k1;
		this->rightPoint_.y_ += k2;
	}
}

// ����������� ������ ������ � ���� �������� �� ���� ������� � �������
void Rectangle::move(double k1, double k2)
{
	this->leftPoint_.x_ += k1;
	this->leftPoint_.y_ += k2;
	this->rightPoint_.x_ += k1;
	this->rightPoint_.y_ += k2;
	this->centre_.x_ += k1;
	this->centre_.y_ += k2;
}

// ���������� ���������������
void Rectangle::scale(double k)
{
	this->leftPoint_.x_ = centre_.x_ + k * (leftPoint_.x_ - centre_.x_);
	this->leftPoint_.y_ = centre_.y_ + k * (leftPoint_.y_ - centre_.y_);
	this->rightPoint_.x_ = centre_.x_ + k * (rightPoint_.x_ - centre_.x_);
	this->rightPoint_.y_ = centre_.y_ + k * (rightPoint_.y_ - centre_.y_);
}

// ������ ������ � ������
void Rectangle::print() const
{
	std::cout << "����� ����: (" << leftPoint_.x_ << "; " << leftPoint_.y_ << ") "
		<< "������ ����: (" << rightPoint_.x_ << "; " << rightPoint_.y_ << ") "
		<< "�����: (" << centre_.x_ << "; " << centre_.y_ << ")\n";
}

// �������� ������������ ��������������
void Rectangle::isCorrect() const
{
	if (leftPoint_.x_ < rightPoint_.x_)
	{
		if (leftPoint_.y_ < rightPoint_.y_)
		{
			return;
		}
	}

	throw ErrorNoCorrectRectangle();
}