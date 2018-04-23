#pragma once

#include "Point.h"

using namespace Geometry;

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

Point ^ Point::add(double x, double y, double z)
{
	return gcnew Point(this->sx + x, this->sy + y, this->sz + z);
}

Point ^ Point::add(Point ^ point)
{
	return gcnew Point(this->sx + point->sx, this->sy + point->sy, this->sz + point->sz);
}

Point  ^ Point::operator+(Point ^ point)
{
	return add(point);
}

/*void toString()
{
	return "Point(" + x + ", " + y + ", " + z + ")";
}*/
