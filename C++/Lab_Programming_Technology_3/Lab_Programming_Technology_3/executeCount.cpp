#include "functions.h"

void executeCount(const std::vector<Polygon>& data, const std::string& parameter)
{
	int result = 0;

	if (parameter == "EVEN")
	{
		result = std::count_if(data.begin(), data.end(), [](const Polygon& p)
			{
				return p.points.size() % 2 == 0;
			});
	}
	else if (parameter == "ODD")
	{
		result = std::count_if(data.begin(), data.end(), [](const Polygon& p)
			{
				return p.points.size() % 2 != 0;
			});
	}
	else
	{
		int nVertex = stoi(parameter);
		result = std::count_if(data.begin(), data.end(), [nVertex](const Polygon& p)
			{
				return p.points.size() == nVertex;
			});
	}

	std::cout << result << std::endl;
}