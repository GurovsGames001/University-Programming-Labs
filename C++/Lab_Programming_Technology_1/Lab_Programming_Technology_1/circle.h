#ifndef _CIRCLE
#define _CIRCLE
#include "shape.h"

class Circle : public Shape
{
public:
	Circle() : radius_(0) {};
	Circle(double x, double y, double radius) : centre_(x, y), radius_(radius) { isCorrect(); };
	~Circle() {};

	double getArea() const override; // Вычисление площади
	rectangle_t getFrameRect() const override; // Получение ограничивающего прямоугольника
	void move(point_t newPos) override; // Перемещение центра фигуры в конкретную точку
	void move(double k1, double k2) override; // Перемещение центра фигуры в виде смещений по осям абсцисс и ординат
	void scale(double k) override; // Изотропное масштабирование
	void print() const override; // Печать данных о фигуре

private:
	point_t centre_;
	double radius_;

	void isCorrect() const override; // Проверка корректности прямоугольника
};

#endif