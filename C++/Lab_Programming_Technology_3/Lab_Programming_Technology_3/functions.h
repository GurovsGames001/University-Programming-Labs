#ifndef _FUNCTIONS_H
#define _FUNCTIONS_H
#include <string>
#include <functional>
#include <algorithm>
#include <numeric>
#include <iomanip>
#include <iostream>
#include "structs.h"

void executeArea(const std::vector<Polygon>& data, const std::string& parameter);
void executeMax(const std::vector<Polygon>& data, const std::string& parameter);
void executeMin(const std::vector<Polygon>& data, const std::string& parameter);
void executeCount(const std::vector<Polygon>& data, const std::string& parameter);
void executeMaxseq(const std::vector<Polygon>& data, const Polygon& parameter);
void executeEcho(std::vector<Polygon>& data, const Polygon& parameter);

double getArea(const Polygon& p);

#endif