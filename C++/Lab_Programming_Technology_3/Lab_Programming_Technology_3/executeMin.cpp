#include "functions.h"

void executeMin(const std::vector<Polygon>& data, const std::string& parameter)
{
	using namespace std::placeholders;

	if (parameter == "AREA")
	{
		auto getAreas = std::bind(getArea, _1);
		auto getMinArea = std::bind(std::less<double>(), std::bind(getAreas, _1), std::bind(getAreas, _2));
		auto minArea = std::min_element(data.begin(), data.end(), getMinArea);
		double result = getArea(*minArea);

		std::cout << std::fixed << std::setprecision(1) << result << std::endl;
	}
	else
	{
		auto minVertexes = std::min_element(data.begin(), data.end(), [](const Polygon& a, const Polygon& b)
			{
				return a.points.size() < b.points.size();
			});

		int result = minVertexes->points.size();

		std::cout << result << std::endl;
	}
}