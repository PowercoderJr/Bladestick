#include "Cylinder.h"
#include "Utils.h"

using namespace Bladestick::Drawing::Geometry;

Cylinder::Cylinder(Vector3D ^ bottomCenter, double exRadius, double height)
{
	this->bottomCenter = bottomCenter;
	this->exRadius = exRadius;
	this->height = height;
	update();
}

void Cylinder::update()
{
	updatePoints();
	updateFacets();
}

void Cylinder::updatePoints()
{
	this->topCenter = bottomCenter + gcnew Vector3D(0, 0, height);
	exBottomPoints = gcnew array<Vector3D^>(N_CIRCLE_POINTS);
	exTopPoints = gcnew array<Vector3D^>(N_CIRCLE_POINTS);
	double dAlpha = Bladestick::degToRad(360.0 / N_CIRCLE_POINTS);
	double alpha = 0;
	for (int i = 0; i < N_CIRCLE_POINTS; ++i)
	{
		double x = bottomCenter->x + exRadius * System::Math::Cos(alpha);
		double y = bottomCenter->y + exRadius * System::Math::Sin(alpha);
		exBottomPoints[i] = gcnew Vector3D(x, y, bottomCenter->z);
		exTopPoints[i] = gcnew Vector3D(x, y, topCenter->z);
		alpha += dAlpha;
	}
}

void Cylinder::updateFacets()
{
	exFacets = gcnew array<Facet^>(N_SIZE_FACETS);
	topCircleFacets = gcnew array<Facet^>(N_CIRCLE_FACETS);
	bottomCircleFacets = gcnew array<Facet^>(N_CIRCLE_FACETS);
	for (int i = 0; i < N_SIZE_FACETS; i += 2)
	{
		exFacets[i] = gcnew Facet(exBottomPoints[i], exBottomPoints[i + 1], exTopPoints[i]);
		exFacets[i + 1] = gcnew Facet(exTopPoints[i], exTopPoints[i + 1], exBottomPoints[i + 1]);

		bottomCircleFacets[i] = gcnew Facet(exBottomPoints[i / 2], bottomCenter, exBottomPoints[i / 2 + 1]);
		topCircleFacets[i] = gcnew Facet(exTopPoints[i / 2], topCenter, exTopPoints[i / 2 + 1]);
	}
}

Vector3D ^ Cylinder::getBottomCenter()
{
	return bottomCenter;
}

void Cylinder::setBottomCenter(Vector3D ^ bottomCenter)
{
	this->bottomCenter = bottomCenter;
}

Vector3D ^ Cylinder::getTopCenter()
{
	return topCenter;
}

void Cylinder::setTopCenter(Vector3D ^ topCenter)
{
	this->topCenter = topCenter;
}

double Cylinder::getExRadius()
{
	return exRadius;
}

void Cylinder::setExRadius(double exRadius)
{
	this->exRadius = exRadius;
}

double Cylinder::getHeight()
{
	return height;
}

void Cylinder::setHeight(double height)
{
	this->height = height;
}

array<Vector3D^> ^ Cylinder::getExBottomPoints()
{
	return exBottomPoints;
}

array<Vector3D^> ^ Cylinder::getExTopPoints()
{
	return exTopPoints;
}

array<Facet^> ^ Cylinder::getExFacets()
{
	return exFacets;
}

array<Facet^> ^ Cylinder::getTopCircleFacets()
{
	return topCircleFacets;
}

array<Facet^> ^ Cylinder::getBottomCircleFacets()
{
	return bottomCircleFacets;
}
