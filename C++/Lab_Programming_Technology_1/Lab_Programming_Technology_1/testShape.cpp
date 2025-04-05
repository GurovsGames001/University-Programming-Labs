#include <memory>
#include <iostream>
#include "shape.h"

void testShape(std::shared_ptr<Shape> shape)
{
	std::cout << "Площадь: " << shape->getArea() << '\n';

	rectangle_t rectangle;
	rectangle = shape->getFrameRect();
	std::cout << "Ширина ограничивающего прямоугольника: " << rectangle.width_ << '\n';
	std::cout << "Высота ограничивающего прямоугольника: " << rectangle.height_ << '\n';
	std::cout << "Центр ограничивающего прямоугольника: (" << rectangle.pos_.x_ << "; " << rectangle.pos_.y_ << ")\n";

	point_t point(10.1, -15.5);
	std::cout << "Фигура в начальной позиции: ";
	shape->print();
	shape->move(point);
	std::cout << "Фигура после перемещения центра в точку: ";
	shape->print();
	shape->move(5.5, 7.5);
	std::cout << "Фигура после перемещения центра по осям: ";
	shape->print();
	
	std::cout << "Фигура до масштабирования: ";
	shape->print();
	shape->scale(3);
	std::cout << "Фигура после масштабирования: ";
	shape->print();
}