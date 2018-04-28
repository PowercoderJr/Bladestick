#pragma once

#include "Facet.h"
#include "Utils.h"

using namespace Bladestick::Drawing::Geometry;
//using namespace System::Drawing;

Facet::Facet(array<Point^> ^ vertices, System::Drawing::Color ^ color)
{
	this->vertices = vertices;
	this->color = color;
}

Facet::Facet(array<Point^> ^ vertices) : Facet::Facet(vertices, System::Drawing::Color::Black) {}

Facet::Facet(Point ^ p1, Point ^ p2, Point ^ p3, System::Drawing::Color ^ color) : Facet::Facet(gcnew array<Point^>(3), color)
{
	//TODO?: можно обойтись без тела?
	vertices->SetValue(p1, 0);
	vertices->SetValue(p2, 1);
	vertices->SetValue(p3, 2);
}

Facet::Facet(Point ^ p1, Point ^ p2, Point ^ p3) : Facet::Facet(p1, p2, p3, System::Drawing::Color::Black) {}

Facet::Facet() : Facet::Facet(gcnew Point(), gcnew Point(), gcnew Point()) {}

void Facet::draw(Bladestick::Drawing::ZBuffer ^ buffer)
{
	if (vertices[0]->y == vertices[1]->y && vertices[0]->y == vertices[2]->y) return;

	if (vertices[0]->y > vertices[1]->y) Bladestick::swap(vertices, 0, 1);
	if (vertices[0]->y > vertices[2]->y) Bladestick::swap(vertices, 0, 2);
	if (vertices[1]->y > vertices[2]->y) Bladestick::swap(vertices, 1, 2);

	System::Drawing::Color ^ edgeColor = System::Drawing::Color::SeaGreen;
	buffer->drawLine(edgeColor, vertices[0], vertices[1]);
	buffer->drawLine(edgeColor, vertices[1], vertices[2]);
	buffer->drawLine(edgeColor, vertices[2], vertices[0]);

	int totHeight = vertices[2]->y - vertices[0]->y;
	for (int i = 0; i < totHeight; i++)
	{
		bool secondHalf = i > vertices[1]->y - vertices[0]->y || vertices[1]->y == vertices[0]->y;
		int segmentHeight = secondHalf ? vertices[2]->y - vertices[1]->y : vertices[1]->y - vertices[0]->y;
		double alpha = (double)i / totHeight;
		double beta = (double)(i - (secondHalf ? vertices[1]->y - vertices[0]->y : 0)) / segmentHeight; // be careful: with above conditions no division by zero here
		Point ^ A = vertices[0] + (vertices[2] - vertices[0]) * alpha;
		Point ^ B = secondHalf ? vertices[1] + (vertices[2] - vertices[1]) * beta : vertices[0] + (vertices[1] - vertices[0]) * beta;
		if (A->x > B->x) Bladestick::swap(&A, &B);
		for (int j = A->x; j <= B->x; j++)
			buffer->setPixel(j, vertices[0]->y + i, 0, color); // attention, due to int casts vertices[0]->y+i != A.y
	}
}

array<Bladestick::Drawing::Geometry::Point^> ^ Facet::getVertices()
{
	return vertices;
}

void Facet::setVertices(array<Point^> ^ vertices)
{
	this->vertices = vertices;
}

System::Drawing::Color ^ Facet::getColor()
{
	return color;
}

void Facet::setColor(System::Drawing::Color ^ color)
{
	this->color = color;
}
