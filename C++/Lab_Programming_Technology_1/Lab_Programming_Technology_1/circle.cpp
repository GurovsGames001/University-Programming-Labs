#define _USE_MATH_DEFINES
#include "circle.h"
#include <cmath>
#include <iostream>

// Вычисление площади
double Circle::getArea() const
{
	return M_PI * radius_ * radius_;
}

// Получение ограничивающего прямоугольника
rectangle_t Circle::getFrameRect() const
{
	rectangle_t temp;

	temp.width_ = 2 * radius_;
	temp.height_ = 2 * radius_;
	temp.pos_ = centre_;

	return temp;
}

// Перемещение центра фигуры в конкретную точку
void Circle::move(point_t newPos)
{
	if ((newPos.x_ != centre_.x_) || (newPos.y_ != centre_.y_))
	{
		this->centre_ = newPos;
	}
}

// Перемещение центра фигуры в виде смещений по осям абсцисс и ординат
void Circle::move(double k1, double k2)
{
	this->centre_.x_ += k1;
	this->centre_.y_ += k2;
}

// Изотропное масштабирование
void Circle::scale(double k)
{
	this->radius_ *= k;
}

// Печать данных о фигуре
void Circle::print() const
{
	std::cout << "Радиус: " << radius_
		<< " Центр: (" << centre_.x_ << "; " << centre_.y_ << ")\n";
}

// Проверка корректности прямоугольника
void Circle::isCorrect() const
{
	if (radius_ <= 0)
	{
		throw ErrorNoCorrectCircle();
	}
}