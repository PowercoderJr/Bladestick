#include "HollowCylinder.h"
#include "Utils.h"

using namespace Geometry;

HollowCylinder::HollowCylinder(Point ^ bottomCenter, double exRadius, double inRadius, double height) : Cylinder::Cylinder(bottomCenter, exRadius, height)
{	
	this->inRadius = inRadius;
	update();
}

void HollowCylinder::update()
{
	updatePoints();
	updateFacets();
}

void HollowCylinder::updatePoints()
{
	Cylinder::Cylinder::updatePoints();
	inBottomPoints = gcnew array<Point^>(N_CIRCLE_POINTS);
	inTopPoints = gcnew array<Point^>(N_CIRCLE_POINTS);
	double dAlpha = degToRad(360.0 / N_CIRCLE_POINTS);
	double alpha = 0;
	for (int i = 0; i < N_CIRCLE_POINTS; ++i)
	{
		double x = bottomCenter->sx + inRadius * System::Math::Cos(alpha);
		double y = bottomCenter->sy + inRadius * System::Math::Sin(alpha);
		inBottomPoints[i] = gcnew Point(x, y, bottomCenter->sz);
		inTopPoints[i] = gcnew Point(x, y, topCenter->sz);
		alpha += dAlpha;
	}
}

void HollowCylinder::updateFacets()
{
	exFacets = gcnew array<Facet^>(N_SIZE_FACETS);
	inFacets = gcnew array<Facet^>(N_SIZE_FACETS);
	topCircleFacets = gcnew array<Facet^>(N_CIRCLE_FACETS);
	bottomCircleFacets = gcnew array<Facet^>(N_CIRCLE_FACETS);
	for (int i = 0; i < N_SIZE_FACETS; i += 2)
	{
		exFacets[i] = gcnew Facet(exBottomPoints[i], exBottomPoints[i + 1], exTopPoints[i]);
		exFacets[i + 1] = gcnew Facet(exTopPoints[i], exTopPoints[i + 1], exBottomPoints[i + 1]);
		inFacets[i] = gcnew Facet(inBottomPoints[i], inBottomPoints[i + 1], inTopPoints[i]);
		inFacets[i + 1] = gcnew Facet(inTopPoints[i], inTopPoints[i + 1], inBottomPoints[i + 1]);

		bottomCircleFacets[i] = gcnew Facet(exBottomPoints[i], exBottomPoints[i + 1], inBottomPoints[i]);
		bottomCircleFacets[i + 1] = gcnew Facet(inBottomPoints[i], inBottomPoints[i + 1], exBottomPoints[i + 1]);
		topCircleFacets[i] = gcnew Facet(exTopPoints[i], exTopPoints[i + 1], inTopPoints[i]);
		topCircleFacets[i + 1] = gcnew Facet(inTopPoints[i], inTopPoints[i + 1], exTopPoints[i + 1]);
	}
}

double HollowCylinder::getInRadius()
{
	return inRadius;
}

void HollowCylinder::setInRadius(double inRadius)
{
	this->inRadius = inRadius;
}

array<Point^> ^ HollowCylinder::getInBottomPoints()
{
	return inBottomPoints;
}

array<Point^> ^ HollowCylinder::getInTopPoints()
{
	return inTopPoints;
}

array<Facet^> ^ HollowCylinder::getInFacets()
{
	return inFacets;
}
