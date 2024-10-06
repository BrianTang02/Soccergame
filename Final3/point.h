#pragma once
#include "Header.h"

struct Point {
	double x, y;
	Point operator+(const Point& t);
	Point operator-(const Point& t);
	Point& operator+=(const Point& t);
	Point& operator-=(const Point& t);
};
