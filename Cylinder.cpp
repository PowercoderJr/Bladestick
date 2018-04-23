#include "Cylinder.h"
#include "Utils.h"

using namespace Geometry;

Cylinder::Cylinder(Point ^ bottomCenter, double exRadius, double height)
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
	this->topCenter = bottomCenter + gcnew Point(0, 0, height);
	exBottomPoints = gcnew array<Point^>(N_CIRCLE_POINTS);
	exTopPoints = gcnew array<Point^>(N_CIRCLE_POINTS);
	double dAlpha = degToRad(360.0 / N_CIRCLE_POINTS);
	double alpha = 0;
	for (int i = 0; i < N_CIRCLE_POINTS; ++i)
	{
		double x = bottomCenter->sx + exRadius * System::Math::Cos(alpha);
		double y = bottomCenter->sy + exRadius * System::Math::Sin(alpha);
		exBottomPoints[i] = gcnew Point(x, y, bottomCenter->sz);
		exTopPoints[i] = gcnew Point(x, y, topCenter->sz);
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

Point ^ Cylinder::getBottomCenter()
{
	return bottomCenter;
}

void Cylinder::setBottomCenter(Point ^ bottomCenter)
{
	this->bottomCenter = bottomCenter;
}

Point ^ Cylinder::getTopCenter()
{
	return topCenter;
}

void Cylinder::setTopCenter(Point ^ topCenter)
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

array<Point^> ^ Cylinder::getExBottomPoints()
{
	return exBottomPoints;
}

array<Point^> ^ Cylinder::getExTopPoints()
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
