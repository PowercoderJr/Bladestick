#pragma once

#include "Vector3D.h"
#include "Utils.h"
#include "Matrix.h"

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
	this->x += x;
	this->y += y;
	this->z += z;
}

void Vector3D::scale(double a, double b, double c)
{
	throw gcnew System::NotImplementedException();
}

void Vector3D::rotate(double alphaDeg, double betaDeg, double gammaDeg)
{
	double alpha = degToRad(alphaDeg);
	double beta = degToRad(betaDeg);
	double gamma = degToRad(gammaDeg);


	using namespace System;
#define sin Math::Sin
#define cos Math::Cos
	Matrix ^ vector = gcnew Matrix(1, 4);
	vector(0, 0) = x;
	vector(0, 1) = y;
	vector(0, 2) = z;
	vector(0, 3) = 1;
	Matrix ^ xRot = gcnew Matrix(4, 4);
	xRot(0, 0) = 1;
	xRot(1, 1) = cos(alpha);
	xRot(1, 2) = sin(alpha);
	xRot(2, 1) = -sin(alpha);
	xRot(2, 2) = cos(alpha);
	xRot(3, 3) = 1;
	vector = vector * xRot;
	x = vector(0, 0);
	y = vector(0, 1);
	z = vector(0, 2);
#undef sin
#undef cos
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
	return gcnew Vector3D(this->/*s*/x + x, this->/*s*/y + y, this->/*s*/z + z);
}

/*Vector3D ^ Vector3D::add(double x)
{
	return add(x, x, x);
}

Vector3D ^ Vector3D::add(Vector3D ^ vector)
{
	return add(vector->sx, vector->sy, vector->sz);
}*/

Vector3D ^ Vector3D::operator+(double x)
{
	return add(x, x, x);
}

Vector3D  ^ Vector3D::operator+(Vector3D ^ vector)
{
	return add(vector->/*s*/x, vector->/*s*/y, vector->/*s*/z);
}

Vector3D ^ Vector3D::subtract(double x, double y, double z)
{
	return add(-x, -y, -z);
}

/*Vector3D ^ Vector3D::subtract(double x)
{
	return subtract(x, x, x);
}

Vector3D ^ Vector3D::subtract(Vector3D ^ vector)
{
	return subtract(vector->x, vector->y, vector->z);
}*/

Vector3D ^ Vector3D::operator-(double x)
{
	return operator+(-x);
}

Vector3D ^ Vector3D::operator-(Vector3D ^ vector)
{
	return subtract(vector->/*s*/x, vector->/*s*/y, vector->/*s*/z);
}

Vector3D ^ Vector3D::operator-()
{
	return gcnew Vector3D(-this->/*s*/x, -this->/*s*/y, -this->/*s*/z + z);
}

Vector3D ^ Vector3D::multiply(double x, double y, double z)
{
	return gcnew Vector3D(this->/*s*/x * x, this->/*s*/y * y, this->/*s*/z * z);
}

/*Vector3D ^ Vector3D::multiply(double x)
{
	return multiply(x, x, x);
}

Vector3D ^ Vector3D::multiply(Vector3D ^ vector)
{
	return multiply(vector->sx, vector->sy, vector->sz);
}*/

Vector3D ^ Vector3D::operator*(double x)
{
	return multiply(x, x, x);
}

Vector3D ^ Vector3D::operator*(Vector3D ^ vector)
{
	return multiply(vector->/*s*/x, vector->/*s*/y, vector->/*s*/z);
}

Vector3D ^ Vector3D::divide(double x, double y, double z)
{
	return multiply(1.0 / x, 1.0 / y, 1.0 / z);
}

/*Vector3D ^ Vector3D::divide(double x)
{
	return divide(x, x, x);
}

Vector3D ^ Vector3D::divide(Vector3D ^ vector)
{
	return divide(vector->sx, vector->sy, vector->sz);
}*/

Vector3D ^ Vector3D::operator/(double x)
{
	return divide(x, x, x);
}

Vector3D ^ Vector3D::operator/(Vector3D ^ vector)
{
	return divide(vector->/*s*/x, vector->/*s*/y, vector->/*s*/z);
}

/*void toString()
{
	return "Vector3D(" + x + ", " + y + ", " + z + ")";
}*/
