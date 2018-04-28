#pragma once

#include "Point.h"

using namespace Bladestick::Drawing::Geometry;

Point::Point(double x, double y, double z, double w, double sx, double sy, double sz, double sw)
{
	this->x = x;
	this->y = y;
	this->z = z;
	this->w = w;
	this->sx = sx;
	this->sy = sy;
	this->sz = sz;
	this->sw = sw;
}

Point::Point(double x, double y, double z, double w) : Point::Point(x, y, z, w, x, y, z, w) {}

Point::Point(double x, double y, double z) : Point::Point(x, y, z, 1) {}

Point::Point(const Point % point) :
	Point::Point(point.x, point.y, point.z, point.w, point.sx, point.sy, point.sz, point.sw) {}

Point::Point() : Point::Point(0, 0, 0) {}

double Point::getX()
{
	return x;
}

void Point::setX(double x)
{
	this->x = x;
}

double Point::getY()
{
	return y;
}

void Point::setY(double y)
{
	this->y = y;
}

double Point::getZ()
{
	return z;
}

void Point::setZ(double z)
{
	this->z = z;
}

double Point::getW()
{
	return w;
}

void Point::setW(double w)
{
	this->w = w;
}

double Point::getSx()
{
	return sx;
}

double Point::getSy()
{
	return sy;
}

double Point::getSz()
{
	return sz;
}

double Point::getSw()
{
	return sw;
}

Point Point::operator=(Point point)
{
	this->x = x;
	this->y = y;
	this->z = z;
	this->w = w;
	this->sx = sx;
	this->sy = sy;
	this->sz = sz;
	this->sw = sw;
	return *this;
}

Point ^ Point::operator=(Point ^ point)
{
	this->x = x;
	this->y = y;
	this->z = z;
	this->w = w;
	this->sx = sx;
	this->sy = sy;
	this->sz = sz;
	this->sw = sw;
	return this;
}

Point ^ Point::add(double x, double y, double z)
{
	return gcnew Point(this->sx + x, this->sy + y, this->sz + z);
}

Point ^ Point::add(double x)
{
	return add(x, x, x);
}

Point ^ Point::add(Point ^ point)
{
	return add(point->sx, point->sy, point->sz);
}

Point ^ Point::operator+(double x)
{
	return add(x);
}

Point  ^ Point::operator+(Point ^ point)
{
	return add(point);
}

Point ^ Point::subtract(double x, double y, double z)
{
	return add(-x, -y, -z);
}

Point ^ Point::subtract(double x)
{
	return subtract(x, x, x);
}

Point ^ Point::subtract(Point ^ point)
{
	return subtract(point->x, point->y, point->z);
}

Point ^ Point::operator-(double x)
{
	return add(x);
}

Point ^ Point::operator-(Point ^ point)
{
	return subtract(point);
}

Point ^ Point::operator-()
{
	return gcnew Point(-this->sx, -this->sy, -this->sz + z);
}

Point ^ Point::multiply(double x, double y, double z)
{
	return gcnew Point(this->sx * x, this->sy * y, this->sz * z);
}

Point ^ Point::multiply(double x)
{
	return multiply(x, x, x);
}

Point ^ Point::multiply(Point ^ point)
{
	return multiply(point->sx, point->sy, point->sz);
}

Point ^ Point::operator*(double x)
{
	return multiply(x);
}

Point ^ Point::operator*(Point ^ point)
{
	return multiply(point);
}

/*void toString()
{
	return "Point(" + x + ", " + y + ", " + z + ")";
}*/
