#include "Box.h"

using namespace Geometry;

Box::Box(Point ^ bottomCenter, double width, double length, double height)
{
	this->width = width;
	this->length = length;
	this->height = height;

	this->corner1 = gcnew Point(bottomCenter->sx - width / 2, bottomCenter->sy - length / 2, bottomCenter->sz);
	this->corner2 = gcnew Point(bottomCenter->sx + width / 2, bottomCenter->sy + length / 2, bottomCenter->sz + height);
	update();
}

Box::Box(Point ^ corner1, Point ^ corner2)
{
	this->width = corner2->sx - corner1->sx;
	this->length = corner2->sy - corner1->sy;
	this->height = corner2->sz - corner1->sz;
	this->corner1 = corner1;
	this->corner2 = corner2;
	updatePoints();
	updateFacets();
}

void Box::update()
{
	updatePoints();
	updateFacets();
}

void Box::updatePoints()
{
	vertices = gcnew array<Point^>(N_VERTICES)
	{
		gcnew Point(corner1->sx, corner1->sy, corner1->sz),		//0 - левый ближний нижний
			gcnew Point(corner1->sx, corner2->sy, corner1->sz), //1 - левый дальний нижний
			gcnew Point(corner2->sx, corner1->sy, corner1->sz), //2 - правый ближний нижний
			gcnew Point(corner2->sx, corner2->sy, corner1->sz), //3 - правый дальний нижний
			gcnew Point(corner1->sx, corner1->sy, corner2->sz), //4 - левый ближний верхний
			gcnew Point(corner1->sx, corner2->sy, corner2->sz), //5 - левый дальний верхний
			gcnew Point(corner2->sx, corner1->sy, corner2->sz), //6 - правый ближний верхний
			gcnew Point(corner2->sx, corner2->sy, corner2->sz)	//7 - правый дальний верхний
	};
}

void Box::updateFacets()
{
	facets = gcnew array<Facet^>(N_FACETS)
	{
		gcnew Facet(vertices[0], vertices[1], vertices[2]),
			gcnew Facet(vertices[1], vertices[2], vertices[3]),
			gcnew Facet(vertices[0], vertices[1], vertices[4]),
			gcnew Facet(vertices[1], vertices[4], vertices[5]),
			gcnew Facet(vertices[1], vertices[3], vertices[5]),
			gcnew Facet(vertices[3], vertices[5], vertices[7]),
			gcnew Facet(vertices[2], vertices[3], vertices[6]),
			gcnew Facet(vertices[3], vertices[6], vertices[7]),
			gcnew Facet(vertices[0], vertices[2], vertices[4]),
			gcnew Facet(vertices[2], vertices[4], vertices[6]),
			gcnew Facet(vertices[4], vertices[5], vertices[6]),
			gcnew Facet(vertices[5], vertices[6], vertices[7])
	};
}

double Box::getWidth()
{
	return width;
}

void Box::setWidth(double width)
{
	this->width = width;
}

double Box::getLength()
{
	return length;
}

void Box::setLength(double length)
{
	this->length = length;
}

double Box::getHeight()
{
	return height;
}

void Box::setHeight(double height)
{
	this->height = height;
}

array<Point^> ^ Box::getVertices()
{
	return vertices;
}

array<Facet^> ^ Box::getFacets()
{
	return facets;
}
