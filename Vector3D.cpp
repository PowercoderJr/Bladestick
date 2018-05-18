#pragma once

#include "Vector3D.h"
#include "Utils.h"
#include "Matrix.h"

using namespace Bladestick::Drawing;

Vector3D::Vector3D(double x, double y, double z, double w, double mx, double my, double mz, double mw)
{
	this->x = x;
	this->y = y;
	this->z = z;
	this->w = w;
	this->mx = mx;
	this->my = my;
	this->mz = mz;
	this->mw = mw;
}

Vector3D::Vector3D(double x, double y, double z, double w) : Vector3D::Vector3D(x, y, z, w, x, y, z, w) {}

Vector3D::Vector3D(double x, double y, double z) : Vector3D::Vector3D(x, y, z, 1) {}

Vector3D::Vector3D(const Vector3D % vector) :
	Vector3D::Vector3D(vector.x, vector.y, vector.z, vector.w, vector.mx, vector.my, vector.mz, vector.mw) {}

Vector3D::Vector3D() : Vector3D::Vector3D(0, 0, 0) {}

#pragma region Operators
Vector3D Vector3D::operator=(Vector3D vector)
{
	this->x = x;
	this->y = y;
	this->z = z;
	this->w = w;
	this->mx = mx;
	this->my = my;
	this->mz = mz;
	this->mw = mw;
	return *this;
}

Vector3D ^ Vector3D::operator=(Vector3D ^ vector)
{
	this->x = x;
	this->y = y;
	this->z = z;
	this->w = w;
	this->mx = mx;
	this->my = my;
	this->mz = mz;
	this->mw = mw;
	return this;
}

Vector3D ^ Vector3D::add(double x, double y, double z)
{
	return gcnew Vector3D(this->x + x, this->y + y, this->z + z);
}

Vector3D ^ Vector3D::operator+(double x)
{
	return add(x, x, x);
}

Vector3D ^ Vector3D::operator+(Vector3D ^ vector)
{
	return add(vector->x, vector->y, vector->z);
}

Vector3D ^ Vector3D::subtract(double x, double y, double z)
{
	return add(-x, -y, -z);
}

Vector3D ^ Vector3D::operator-(double x)
{
	return operator+(-x);
}

Vector3D ^ Vector3D::operator-(Vector3D ^ vector)
{
	return subtract(vector->x, vector->y, vector->z);
}

Vector3D ^ Vector3D::operator-()
{
	return gcnew Vector3D(-this->x, -this->y, -this->z);
}
#pragma endregion

Vector3D ^ Vector3D::scale(double x, double y, double z)
{
	return gcnew Vector3D(this->x * x, this->y * y, this->z * z);
}

Vector3D ^ Vector3D::scale(double x)
{
	return scale(x, x, x);
}

double Vector3D::getMagnitude()
{
	return System::Math::Sqrt(x * x + y * y + z * z);
}

Vector3D ^ Vector3D::normalized()
{
	double m = getMagnitude();
	return gcnew Vector3D(x / m, y / m, z / m);
}
