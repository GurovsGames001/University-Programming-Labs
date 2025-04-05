#include "functions.h"

void executeMax(const std::vector<Polygon>& data, const std::string& parameter)
{
	using namespace std::placeholders;

	if (parameter == "AREA")
	{
		auto getAreas = std::bind(getArea, _1);
		auto getMaxArea = std::bind(std::less<double>(), std::bind(getAreas, _1), std::bind(getAreas, _2));
		auto maxArea = std::max_element(data.begin(), data.end(), getMaxArea);
		double result = getArea(*maxArea);

		std::cout << std::fixed << std::setprecision(1) << result << std::endl;
	}
	else
	{
		auto maxVertexes = std::max_element(data.begin(), data.end(), [](const Polygon& a, const Polygon& b) 
			{
				return a.points.size() < b.points.size();
			});

		int result = maxVertexes->points.size();

		std::cout << result << std::endl;
	}
}