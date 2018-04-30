#pragma once

#include "Vector3D.h"

using namespace Bladestick::Drawing::Geometry;

Vector3D::Vector3D(double x, double y, double z, double w, double sx, double sy, double sz, double sw)
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

Vector3D::Vector3D(double x, double y, double z, double w) : Vector3D::Vector3D(x, y, z, w, x, y, z, w) {}

Vector3D::Vector3D(double x, double y, double z) : Vector3D::Vector3D(x, y, z, 1) {}

Vector3D::Vector3D(const Vector3D % vector) :
	Vector3D::Vector3D(vector.x, vector.y, vector.z, vector.w, vector.sx, vector.sy, vector.sz, vector.sw) {}

Vector3D::Vector3D() : Vector3D::Vector3D(0, 0, 0) {}

void Vector3D::move(double x, double y, double z)
{
	throw gcnew System::NotImplementedException();
}

void Vector3D::scale(double a, double b, double c)
{
	throw gcnew System::NotImplementedException();
}

void Vector3D::rotate(double alpha, double beta, double gamma)
{
	throw gcnew System::NotImplementedException();
}

double Vector3D::getX()
{
	return x;
}

void Vector3D::setX(double x)
{
	this->x = x;
}

double Vector3D::getY()
{
	return y;
}

void Vector3D::setY(double y)
{
	this->y = y;
}

double Vector3D::getZ()
{
	return z;
}

void Vector3D::setZ(double z)
{
	this->z = z;
}

double Vector3D::getW()
{
	return w;
}

void Vector3D::setW(double w)
{
	this->w = w;
}

double Vector3D::getSx()
{
	return sx;
}

double Vector3D::getSy()
{
	return sy;
}

double Vector3D::getSz()
{
	return sz;
}

double Vector3D::getSw()
{
	return sw;
}

Vector3D Vector3D::operator=(Vector3D vector)
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

Vector3D ^ Vector3D::operator=(Vector3D ^ vector)
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

Vector3D ^ Vector3D::add(double x, double y, double z)
{
	return gcnew Vector3D(this->sx + x, this->sy + y, this->sz + z);
}

Vector3D ^ Vector3D::add(double x)
{
	return add(x, x, x);
}

Vector3D ^ Vector3D::add(Vector3D ^ vector)
{
	return add(vector->sx, vector->sy, vector->sz);
}

Vector3D ^ Vector3D::operator+(double x)
{
	return add(x);
}

Vector3D  ^ Vector3D::operator+(Vector3D ^ vector)
{
	return add(vector);
}

Vector3D ^ Vector3D::subtract(double x, double y, double z)
{
	return add(-x, -y, -z);
}

Vector3D ^ Vector3D::subtract(double x)
{
	return subtract(x, x, x);
}

Vector3D ^ Vector3D::subtract(Vector3D ^ vector)
{
	return subtract(vector->x, vector->y, vector->z);
}

Vector3D ^ Vector3D::operator-(double x)
{
	return add(x);
}

Vector3D ^ Vector3D::operator-(Vector3D ^ vector)
{
	return subtract(vector);
}

Vector3D ^ Vector3D::operator-()
{
	return gcnew Vector3D(-this->sx, -this->sy, -this->sz + z);
}

Vector3D ^ Vector3D::multiply(double x, double y, double z)
{
	return gcnew Vector3D(this->sx * x, this->sy * y, this->sz * z);
}

Vector3D ^ Vector3D::multiply(double x)
{
	return multiply(x, x, x);
}

Vector3D ^ Vector3D::multiply(Vector3D ^ vector)
{
	return multiply(vector->sx, vector->sy, vector->sz);
}

Vector3D ^ Vector3D::operator*(double x)
{
	return multiply(x);
}

Vector3D ^ Vector3D::operator*(Vector3D ^ vector)
{
	return multiply(vector);
}

Vector3D ^ Vector3D::divide(double x, double y, double z)
{
	return multiply(1.0 / x, 1.0 / y, 1.0 / z);
}

Vector3D ^ Vector3D::divide(double x)
{
	return divide(x, x, x);
}

Vector3D ^ Vector3D::divide(Vector3D ^ vector)
{
	return divide(vector->sx, vector->sy, vector->sz);
}

Vector3D ^ Vector3D::operator/(double x)
{
	return divide(x);
}

Vector3D ^ Vector3D::operator/(Vector3D ^ vector)
{
	return divide(vector);
}

/*void toString()
{
	return "Vector3D(" + x + ", " + y + ", " + z + ")";
}*/
