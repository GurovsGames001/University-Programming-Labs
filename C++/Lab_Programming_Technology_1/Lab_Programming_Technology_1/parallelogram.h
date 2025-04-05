#ifndef _PARALLELOGRAM
#define _PARALLELOGRAM
#include "shape.h"

class Parallelogram : public Shape
{
public:
	Parallelogram() {};
	Parallelogram(double x1, double y1, double x2, double y2, double x3, double y3);
	~Parallelogram() {};

	double getArea() const override; // Вычисление площади
	rectangle_t getFrameRect() const override; // Получение ограничивающего прямоугольника
	void move(point_t newPos) override; // Перемещение центра фигуры в конкретную точку
	void move(double k1, double k2) override; // Перемещение центра фигуры в виде смещений по осям абсцисс и ординат
	void scale(double k) override; // Изотропное масштабирование
	void print() const override; // Печать данных о фигуре

private:
	point_t vertex1_;
	point_t vertex2_;
	point_t vertex3_;
	point_t centre_;

	void isCorrect() const override; // Проверка корректности прямоугольника
};

#endif