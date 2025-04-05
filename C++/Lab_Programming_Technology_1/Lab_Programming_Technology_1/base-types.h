#ifndef _BASE_TYPES
#define _BASE_TYPES

struct point_t
{
	double x_;
	double y_;
	point_t() : x_(0), y_(0) {};
	point_t(double x, double y): x_(x), y_(y) {};
};

struct rectangle_t
{
	double width_;
	double height_;
	point_t pos_;
	rectangle_t() : width_(0), height_(0) {};
};

#endif