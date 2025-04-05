#ifndef _OVERLOADED_IN_OUT_H
#define _OVERLOADED_IN_OUT_H
#include <iostream>
#include "structs.h"

std::istream& operator>>(std::istream& in, Polygon& ob);
std::istream& operator>>(std::istream& in, Point& ob);
std::istream& operator>>(std::istream& in, DelimiterIO&& dest);
std::istream& operator>>(std::istream& in, Command& dest);

#endif