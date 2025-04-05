#include "functions.h"

void countCopy(std::vector<Polygon>::iterator& pos, std::vector<Polygon>& data, const Polygon& parameter, int& result);

void executeEcho(std::vector<Polygon>& data, const Polygon& parameter)
{
	int result = 0;

	// Реализация через цикл
	/*std::vector<Polygon>::iterator pos = data.begin();
	while (pos != data.end())
	{
		pos = std::find_if(pos, data.end(),
			[&parameter](const Polygon& currentPolygon)
			{
				return currentPolygon == parameter;
			});
		if (pos != data.end())
		{
			pos = data.insert(pos + 1, parameter);
			pos++;
			result++;
		}
	}*/

	// Реализация через рекурсию
	std::vector<Polygon>::iterator pos = data.begin();
	countCopy(pos, data, parameter, result);

	std::cout << result << std::endl;
}

void countCopy(std::vector<Polygon>::iterator& pos, std::vector<Polygon>& data, const Polygon& parameter, int& result)
{
	pos = std::find_if(pos, data.end(),
		[&parameter](const Polygon& currentPolygon)
		{
			return currentPolygon == parameter;
		});

	if (pos == data.end())
	{
		return;
	}

	pos = data.insert(pos + 1, parameter);
	pos++;
	result++;

	countCopy(pos, data, parameter, result);
}