#include "Box.h"
#include "Vector3D.h"

using namespace Bladestick::Drawing::Geometry;

Box::Box(Vector3D ^ bottomCenter, double width, double length, double height, System::Drawing::Color ^ color) : AbstractTransformable::AbstractTransformable()
{
	this->width = width;
	this->length = length;
	this->height = height;
	this->color = color;

	this->corner1 = gcnew Vector3D(bottomCenter->x - width / 2, bottomCenter->y - length / 2, bottomCenter->z);
	this->corner2 = gcnew Vector3D(bottomCenter->x + width / 2, bottomCenter->y + length / 2, bottomCenter->z + height);
	this->setOrigin((corner1 + corner2) / 2);
	update();
}

Box::Box(Vector3D ^ corner1, Vector3D ^ corner2, System::Drawing::Color ^ color) : AbstractTransformable::AbstractTransformable()
{
	this->width = corner2->x - corner1->x;
	this->length = corner2->y - corner1->y;
	this->height = corner2->z - corner1->z;
	this->corner1 = corner1;
	this->corner2 = corner2;
	this->color = color;
	this->setOrigin((corner1 + corner2) / 2);
	update();
}

void Box::update()
{
	updatePoints();
	updateFacets();
}

void Box::draw(Bladestick::Drawing::ZBuffer ^ buffer)
{
	for each (Facet ^ facet in facets)
	{
		buffer->drawToBuffer(facet);
	}
}

void Box::updatePoints()
{
	vertices = gcnew array<Vector3D^>(N_VERTICES)
	{
		gcnew Vector3D(corner1->x, corner1->y, corner1->z),		//0 - левый ближний нижний
			gcnew Vector3D(corner1->x, corner2->y, corner1->z), //1 - левый дальний нижний
			gcnew Vector3D(corner2->x, corner1->y, corner1->z), //2 - правый ближний нижний
			gcnew Vector3D(corner2->x, corner2->y, corner1->z), //3 - правый дальний нижний
			gcnew Vector3D(corner1->x, corner1->y, corner2->z), //4 - левый ближний верхний
			gcnew Vector3D(corner1->x, corner2->y, corner2->z), //5 - левый дальний верхний
			gcnew Vector3D(corner2->x, corner1->y, corner2->z), //6 - правый ближний верхний
			gcnew Vector3D(corner2->x, corner2->y, corner2->z)	//7 - правый дальний верхний
	};
}

void Box::updateFacets()
{
	System::Random ^ rnd = gcnew System::Random();
	facets = gcnew array<Facet^>(N_FACETS)
	{
		gcnew Facet(vertices[0], vertices[1], vertices[2], System::Drawing::Color::FromArgb(rnd->Next(256), rnd->Next(256), rnd->Next(256))),
			gcnew Facet(vertices[1], vertices[2], vertices[3], System::Drawing::Color::FromArgb(rnd->Next(256), rnd->Next(256), rnd->Next(256))),
			gcnew Facet(vertices[0], vertices[1], vertices[4], System::Drawing::Color::FromArgb(rnd->Next(256), rnd->Next(256), rnd->Next(256))),
			gcnew Facet(vertices[1], vertices[4], vertices[5], System::Drawing::Color::FromArgb(rnd->Next(256), rnd->Next(256), rnd->Next(256))),
			gcnew Facet(vertices[1], vertices[3], vertices[5], System::Drawing::Color::FromArgb(rnd->Next(256), rnd->Next(256), rnd->Next(256))),
			gcnew Facet(vertices[3], vertices[5], vertices[7], System::Drawing::Color::FromArgb(rnd->Next(256), rnd->Next(256), rnd->Next(256))),
			gcnew Facet(vertices[2], vertices[3], vertices[6], System::Drawing::Color::FromArgb(rnd->Next(256), rnd->Next(256), rnd->Next(256))),
			gcnew Facet(vertices[3], vertices[6], vertices[7], System::Drawing::Color::FromArgb(rnd->Next(256), rnd->Next(256), rnd->Next(256))),
			gcnew Facet(vertices[0], vertices[2], vertices[4], System::Drawing::Color::FromArgb(rnd->Next(256), rnd->Next(256), rnd->Next(256))),
			gcnew Facet(vertices[2], vertices[4], vertices[6], System::Drawing::Color::FromArgb(rnd->Next(256), rnd->Next(256), rnd->Next(256))),
			gcnew Facet(vertices[4], vertices[5], vertices[6], System::Drawing::Color::FromArgb(rnd->Next(256), rnd->Next(256), rnd->Next(256))),
			gcnew Facet(vertices[5], vertices[6], vertices[7], System::Drawing::Color::FromArgb(rnd->Next(256), rnd->Next(256), rnd->Next(256)))
	};
}

void Box::move(double x, double y, double z)
{
	throw gcnew System::NotImplementedException();
}

void Box::scale(double a, double b, double c)
{
	throw gcnew System::NotImplementedException();
}

void Box::rotate(double alphaDeg, double betaDeg, double gammaDeg)
{
	for each (Facet ^ facet in facets)
		facet->rotate(alphaDeg, betaDeg, gammaDeg);
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

array<Vector3D^> ^ Box::getVertices()
{
	return vertices;
}

array<Facet^> ^ Box::getFacets()
{
	return facets;
}
