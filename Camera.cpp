#include "Camera.h"
#include "Vector3D.h"

using namespace Bladestick::Drawing;

Camera::Camera(Vector3D ^ position, Vector3D ^ target, int near, int far, bool perspective)
{
	setPosition(position);
	setTarget(target);
	updateDirs();
	this->near = near;
	this->far = far;
	this->perspective = perspective;
}

void Camera::setPosition(double x, double y, double z)
{
	this->position = gcnew Vector3D(x, y, z);
}

void Camera::setPosition(Vector3D ^ position)
{
	setPosition(position->x, position->y, position->z);
}

void Camera::setTarget(double x, double y, double z)
{
	this->target = gcnew Vector3D(x, y, z);
}

void Camera::setTarget(Vector3D ^ target)
{
	setTarget(target->x, target->y, target->z);
}

void Camera::updateDirs()
{
	backDir = (position - target)->normalized();
	rightDir = (gcnew Vector3D(0, 1, 0))->vectorProduct(backDir)->normalized();
	upDir = backDir->vectorProduct(rightDir)->normalized();
}
