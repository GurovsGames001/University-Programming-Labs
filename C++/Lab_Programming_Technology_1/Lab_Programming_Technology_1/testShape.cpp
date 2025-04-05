#include <memory>
#include <iostream>
#include "shape.h"

void testShape(std::shared_ptr<Shape> shape)
{
	std::cout << "�������: " << shape->getArea() << '\n';

	rectangle_t rectangle;
	rectangle = shape->getFrameRect();
	std::cout << "������ ��������������� ��������������: " << rectangle.width_ << '\n';
	std::cout << "������ ��������������� ��������������: " << rectangle.height_ << '\n';
	std::cout << "����� ��������������� ��������������: (" << rectangle.pos_.x_ << "; " << rectangle.pos_.y_ << ")\n";

	point_t point(10.1, -15.5);
	std::cout << "������ � ��������� �������: ";
	shape->print();
	shape->move(point);
	std::cout << "������ ����� ����������� ������ � �����: ";
	shape->print();
	shape->move(5.5, 7.5);
	std::cout << "������ ����� ����������� ������ �� ����: ";
	shape->print();
	
	std::cout << "������ �� ���������������: ";
	shape->print();
	shape->scale(3);
	std::cout << "������ ����� ���������������: ";
	shape->print();
}