#pragma once

#include "Point.h"

using namespace Geometry;

Point::Point(float x, float y, float z, float w, float sx, float sy, float sz, float sw)
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

Point::Point(float x, float y, float z, float w) : Point::Point(x, y, z, w, x, y, z, w) {}

Point::Point(float x, float y, float z) : Point::Point(x, y, z, 1) {}

Point::Point() : Point::Point(0, 0, 0) {}

float Point::getX()
{
	return x;
}

void Point::setX(float x)
{
	this->x = x;
}

float Point::getY()
{
	return y;
}

void Point::setY(float y)
{
	this->y = y;
}

float Point::getZ()
{
	return z;
}

void Point::setZ(float z)
{
	this->z = z;
}

float Point::getW()
{
	return w;
}

void Point::setW(float w)
{
	this->w = w;
}

float Point::getSx()
{
	return sx;
}

float Point::getSy()
{
	return sy;
}

float Point::getSz()
{
	return sz;
}

float Point::getSw()
{
	return sw;
}

Point^ Point::add(float x, float y, float z)
{
	return gcnew Point(this->sx + x, this->sy + y, this->sz + z);
}

Point^ Point::add(Point^ point)
{
	return gcnew Point(this->sx + point->sx, this->sy + point->sy, this->sz + point->sz);
}

Point ^ Point::operator+(Point^ point)
{
	return add(point);
}

/*void toString()
{
	return "Point(" + x + ", " + y + ", " + z + ")";
}*/
