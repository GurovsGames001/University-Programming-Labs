#include "functions.h"

void executeMaxseq(const std::vector<Polygon>& data, const Polygon& parameter)
{
	int result = 0;
	int max = 0;

	result = std::max(max, std::accumulate(data.begin(), data.end(), 0, [&parameter, &max](int result, const Polygon& currentPolygon)
		{
			if (currentPolygon == parameter)
			{
				max++;
			}
			else
			{
				result = std::max(result, max);
				max = 0;
			}

			return result;
		}));

	std::cout << result << std::endl;
}