#include "Header.h"

Point Point::operator+(const Point& t) {
	return {x + t.x, y + t.y};
}
Point Point::operator-(const Point& t) {
	return {x - t.x, y - t.y};
}
Point& Point::operator+=(const Point& t) {
	x += t.x, y += t.y;
	return *this;
}
Point& Point::operator-=(const Point& t) {
	x -= t.x, y -= t.y;
	return *this;
}
