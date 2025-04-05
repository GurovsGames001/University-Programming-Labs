#ifndef _SHAPE
#define _SHAPE
#include "base-types.h"
#include "exception.h"

class Shape
{
public:
	virtual ~Shape() {};

	virtual double getArea() const = 0; // Вычисление площади
	virtual rectangle_t getFrameRect() const = 0; // Получение ограничивающего прямоугольника
	virtual void move(point_t newPos) = 0; // Перемещение центра фигуры в конкретную точку
	virtual void move(double k1, double k2) = 0; // Перемещение центра фигуры в виде смещений по осям абсцисс и ординат
	virtual void scale(double k) = 0; // Изотропное масштабирование
	virtual void print() const = 0; // Печать данных о фигуре

private:
	point_t centre_;

	virtual void isCorrect() const = 0; // Проверка корректности заданной фигуры
};

#endif