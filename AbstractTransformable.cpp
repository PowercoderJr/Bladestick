#include "AbstractTransformable.h"
#include "Vector3D.h"

using namespace Bladestick::Drawing::Geometry;

AbstractTransformable::AbstractTransformable()
{
	this->xOrigin = 0.0;
	this->yOrigin = 0.0;
	this->zOrigin = 0.0;
	this->xOffset = 0.0;
	this->yOffset = 0.0;
	this->zOffset = 0.0;
	this->xScaling = 1.0;
	this->yScaling = 1.0;
	this->zScaling = 1.0;
	this->xRotationDeg = 0.0;
	this->yRotationDeg = 0.0;
	this->zRotationDeg = 0.0;
}

void AbstractTransformable::setScalingFactors(double a, double b, double c)
{
	this->xScaling = a;
	this->yScaling = b;
	this->zScaling = c;
}

void AbstractTransformable::setScalingFactors(Vector3D ^ factors)
{
	setScalingFactors(factors->x, factors->y, factors->z);
}

void AbstractTransformable::setRotationAngles(double alphaDeg, double betaDeg, double gammaDeg)
{
	this->xRotationDeg = alphaDeg;
	this->yRotationDeg = betaDeg;
	this->zRotationDeg = gammaDeg;
}

void AbstractTransformable::setRotationAngles(Vector3D ^ angles)
{
	setScalingFactors(angles->x, angles->y, angles->z);
}

void AbstractTransformable::setOrigin(double x, double y, double z)
{
	this->xOrigin = x;
	this->yOrigin = y;
	this->zOrigin = z;
}

void AbstractTransformable::setOrigin(Vector3D ^ origin)
{
	setOrigin(origin->x, origin->y, origin->z);
}
