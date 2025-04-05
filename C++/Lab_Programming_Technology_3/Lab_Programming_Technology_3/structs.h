#ifndef _STRUCTS_H
#define _STRUCTS_H
#include <vector>

struct Point
{
	int x, y;

	bool operator==(const Point& otherPoint) const
	{
		return (x == otherPoint.x) && (y == otherPoint.y);
	}
};

struct Polygon
{
	std::vector<Point> points;

	bool operator==(const Polygon& otherPolygon) const
	{
		bool isEqual = points.size() == otherPolygon.points.size();

		if (isEqual)
		{
			isEqual = std::equal(points.begin(), points.end(), otherPolygon.points.begin());
		}

		return isEqual;
	}
};

struct DelimiterIO
{
	char exp;
};

struct Command
{
	std::string command;
	std::string parameter;
	Polygon polygon;
};

#endif