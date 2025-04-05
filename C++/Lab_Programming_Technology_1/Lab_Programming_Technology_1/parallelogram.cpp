#include "parallelogram.h"
#include <iostream>

// Параметризованный конструктор
Parallelogram::Parallelogram(double x1, double y1, double x2, double y2, double x3, double y3) : vertex1_(x1, y1), vertex2_(x2, y2), vertex3_(x3, y3)
{
	if (y2 == y3)
	{
		if (x3 < x2)
		{
			std::swap(vertex1_, vertex3_);
		}
		else
		{
			std::swap(vertex1_, vertex2_);
			std::swap(vertex2_, vertex3_);
		}
	}
	if ((y1 == y2) && (x1 > x2))
	{
		std::swap(vertex1_, vertex2_);
	}

	centre_.x_ = x1 + (x3 - x1) / 2;
	centre_.y_ = y1 + (y3 - y1) / 2;

	isCorrect();
}

// Вычисление площади
double Parallelogram::getArea() const
{
	double height = 0;
	height = abs(vertex3_.y_ - vertex1_.y_);

	return height * (vertex2_.x_ - vertex1_.x_);
}

// Получение ограничивающего прямоугольника
rectangle_t Parallelogram::getFrameRect() const
{
	rectangle_t temp;

	temp.width_ = abs(vertex2_.x_ - vertex1_.x_) + abs(vertex3_.x_ - vertex2_.x_);
	temp.height_ = abs(vertex3_.y_ - vertex1_.y_);
	temp.pos_ = centre_;

	return temp;
}

// Перемещение центра фигуры в конкретную точку
void Parallelogram::move(point_t newPos)
{
	if ((newPos.x_ != centre_.x_) || (newPos.y_ != centre_.y_))
	{
		double k1 = 0;
		double k2 = 0;
		k1 = newPos.x_ - centre_.x_;
		k2 = newPos.y_ - centre_.y_;

		this->centre_ = newPos;

		this->vertex1_.x_ += k1;
		this->vertex1_.y_ += k2;
		this->vertex2_.x_ += k1;
		this->vertex2_.y_ += k2;
		this->vertex3_.x_ += k1;
		this->vertex3_.y_ += k2;
	}
}

// Перемещение центра фигуры в виде смещений по осям абсцисс и ординат
void Parallelogram::move(double k1, double k2)
{
	this->vertex1_.x_ += k1;
	this->vertex1_.y_ += k2;
	this->vertex2_.x_ += k1;
	this->vertex2_.y_ += k2;
	this->vertex3_.x_ += k1;
	this->vertex3_.y_ += k2;
	this->centre_.x_ += k1;
	this->centre_.y_ += k2;
}

// Изотропное масштабирование
void Parallelogram::scale(double k)
{
	this->vertex1_.x_ = centre_.x_ + k * (vertex1_.x_ - centre_.x_);
	this->vertex1_.y_ = centre_.y_ + k * (vertex1_.y_ - centre_.y_);
	this->vertex2_.x_ = centre_.x_ + k * (vertex2_.x_ - centre_.x_);
	this->vertex2_.y_ = centre_.y_ + k * (vertex2_.y_ - centre_.y_);
	this->vertex3_.x_ = centre_.x_ + k * (vertex3_.x_ - centre_.x_);
	this->vertex3_.y_ = centre_.y_ + k * (vertex3_.y_ - centre_.y_);
}

// Печать данных о фигуре
void Parallelogram::print() const
{
	std::cout << "Первая вершина: (" << vertex1_.x_ << "; " << vertex1_.y_ << ") "
		<< "Вторая вершина: (" << vertex2_.x_ << "; " << vertex2_.y_ << ") "
		<< "Третья вершина: (" << vertex3_.x_ << "; " << vertex3_.y_ << ") "
		<< "Центр: (" << centre_.x_ << "; " << centre_.y_ << ")\n";
}

// Проверка корректности прямоугольника
void Parallelogram::isCorrect() const
{
	if ((vertex1_.y_ == vertex2_.y_) && (vertex1_.y_ != vertex3_.y_) &&
		(vertex3_.x_ != vertex1_.x_) && (vertex3_.x_ != vertex2_.x_) && 
		(vertex1_.x_ != vertex2_.x_))
	{
		return;
	}
	
	throw ErrorNoCorrectParallelogram();
}