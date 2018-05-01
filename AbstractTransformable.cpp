#include "AbstractTransformable.h"
#include "Vector3D.h"

using namespace Bladestick::Drawing::Geometry;

AbstractTransformable::AbstractTransformable()
{
	this->origin = gcnew Vector3D(0, 0, 0);
	this->offset = gcnew Vector3D(0, 0, 0);
	this->scaling = gcnew Vector3D(1, 1, 1);
	this->rotationDeg = gcnew Vector3D(0, 0, 0);
}
