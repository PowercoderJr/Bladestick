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

/*void Vector3D::transform()
{
	double alpha = degToRad(xRotationDeg);
	double beta = degToRad(yRotationDeg);
	double gamma = degToRad(zRotationDeg);

	using namespace System;
#define sin Math::Sin
#define cos Math::Cos
	/*mx = x * cos(beta) * cos(gamma) + z * sin(beta) - y * cos(beta) * sin(gamma);
	my = cos(alpha) * (y * cos(gamma) + x * sin(gamma)) - sin(alpha) * (z * cos(beta) - x * cos(gamma) * sin(beta) + y * sin(beta) * sin(gamma));
	mz = sin(alpha) * (y * cos(gamma) + x * sin(gamma)) + cos(alpha) * (z * cos(beta) - x * cos(gamma) * sin(beta) + y * sin(beta) * sin(gamma));*
	mx = xOrigin + cos(gamma) * ((x - xOrigin) * cos(beta) + ((z - zOrigin) * cos(alpha) + (y - yOrigin) * sin(alpha)) * sin(beta)) - ((y - yOrigin) * cos(alpha) - (z - zOrigin) * sin(alpha)) * sin(gamma);
	my = yOrigin + cos(gamma) * ((y - yOrigin) * cos(alpha) - (z - zOrigin) * sin(alpha)) + ((x - xOrigin) * cos(beta) + ((z - zOrigin) * cos(alpha) + (y - yOrigin) * sin(alpha)) * sin(beta)) * sin(gamma);
	mz = zOrigin + cos(beta) * ((z - zOrigin) * cos(alpha) + (y - yOrigin) * sin(alpha)) - (x - xOrigin) * sin(beta);
#undef sin
#undef cos
}*/

/*void Vector3D::scale(double a, double b, double c)
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
	/*Matrix ^ vector = gcnew Matrix(1, 4);
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
	Matrix ^ yRot = gcnew Matrix(4, 4);
	yRot(0, 0) = cos(beta);
	yRot(0, 2) = -sin(beta);
	yRot(1, 1) = 1;
	yRot(2, 0) = sin(beta);
	yRot(2, 2) = cos(beta);
	yRot(3, 3) = 1;
	Matrix ^ zRot = gcnew Matrix(4, 4);
	zRot(0, 0) = cos(gamma);
	zRot(0, 1) = sin(gamma);
	zRot(1, 0) = -sin(gamma);
	zRot(1, 1) = cos(gamma);
	zRot(2, 2) = 1;
	zRot(3, 3) = 1;
	vector = vector * xRot * yRot * zRot;
	mx = vector(0, 0);
	my = vector(0, 1);
	mz = vector(0, 2);
	mx = x * cos(beta) * cos(gamma) + z * sin(beta) - y * cos(beta) * sin(gamma);
	my = cos(alpha) * (y * cos(gamma) + x * sin(gamma)) - sin(alpha) * (z * cos(beta) - x * cos(gamma) * sin(beta) + y * sin(beta) * sin(gamma));
	mz = sin(alpha) * (y * cos(gamma) + x * sin(gamma)) + cos(alpha) * (z * cos(beta) - x * cos(gamma) * sin(beta) + y * sin(beta) * sin(gamma));
#undef sin
#undef cos
}*/

#pragma region Accessors
/*
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
*/
#pragma endregion

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

Vector3D  ^ Vector3D::operator+(Vector3D ^ vector)
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

Vector3D ^ Vector3D::multiply(double x, double y, double z)
{
	return gcnew Vector3D(this->x * x, this->y * y, this->z * z);
}

Vector3D ^ Vector3D::operator*(double x)
{
	return multiply(x, x, x);
}

Vector3D ^ Vector3D::operator*(Vector3D ^ vector)
{
	return multiply(vector->x, vector->y, vector->z);
}

Vector3D ^ Vector3D::divide(double x, double y, double z)
{
	return multiply(1.0 / x, 1.0 / y, 1.0 / z);
}

Vector3D ^ Vector3D::operator/(double x)
{
	return divide(x, x, x);
}

Vector3D ^ Vector3D::operator/(Vector3D ^ vector)
{
	return divide(vector->x, vector->y, vector->z);
}
#pragma endregion
