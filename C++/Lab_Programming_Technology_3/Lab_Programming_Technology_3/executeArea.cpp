#include "functions.h"
#include "exceptions.h"

double getRightArea(const Polygon& p, const std::string& parameter);

void executeArea(const std::vector<Polygon>& data, const std::string& parameter)
{
	using namespace std::placeholders;

	double result = 0;
	auto getAreas = std::bind(getRightArea, _2, std::ref(parameter));
	result = std::accumulate(data.begin(), data.end(), 0, std::bind(std::plus<double>(), _1, getAreas));

	if (parameter == "MEAN")
	{
		if (data.empty())
		{
			throw ErrorVectorIsEmpty();
		}

		result /= data.size();
	}

	std::cout << std::fixed << std::setprecision(1) << result << std::endl;
}

double getRightArea(const Polygon& p, const std::string& parameter)
{
	double area = 0;

	if (parameter == "MEAN")
	{
		area = getArea(p);
	}
	else if (parameter == "EVEN")
	{
		if (p.points.size() % 2 == 0)
		{
			area = getArea(p);
		}
	}
	else if (parameter == "ODD")
	{
		if (p.points.size() % 2 != 0)
		{
			area = getArea(p);
		}
	}
	else
	{
		if (p.points.size() == std::stoi(parameter))
		{
			area = getArea(p);
		}
	}

	return area;
}

double getArea(const Polygon& p)
{
	double area = 0;
	
	for (int i = 0; i < p.points.size() - 1; i++)
	{
		area += ((p.points[i].x * p.points[i + 1].y) - (p.points[i].y * p.points[i + 1].x));
	}
	
	area += ((p.points[p.points.size() - 1].x * p.points[0].y) - (p.points[p.points.size() - 1].y * p.points[0].x));
	
	area = 0.5 * abs(area);
	
	return area;
}