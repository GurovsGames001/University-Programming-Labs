#include <iostream>
#include <memory>
#include "rectangle.h"
#include "circle.h"
#include "parallelogram.h"
#include "testFunction.h"

int main()
{
	setlocale(LC_ALL, "rus");

	try
	{
		std::shared_ptr<Shape> rectangle = std::make_shared<Rectangle>(0, 0, 4, 5);
		std::shared_ptr<Shape> circle = std::make_shared<Circle>(1.5, -2, 9.8);
		std::shared_ptr<Shape> parallelogram = std::make_shared<Parallelogram>(2.4, 1, 8, 1, 6.5, 5.7);

		std::cout << "\n-----------Прямоугольник-----------\n";
		testShape(rectangle);
		std::cout << "\n-----------Круг-----------\n";
		testShape(circle);
		std::cout << "\n-----------Параллелограмм-----------\n";
		testShape(parallelogram);
	}

	catch (const std::exception& error)
	{
		std::cerr << error.what() << '\n';
		return -1;
	}

	return 0;
}