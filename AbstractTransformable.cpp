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

void Bladestick::Drawing::Geometry::AbstractTransformable::setOrigin(Vector3D ^ origin)
{
	this->xOrigin = origin->x;
	this->yOrigin = origin->y;
	this->zOrigin = origin->z;
}
