#pragma once

#include "Facet.h"

using namespace Geometry;

Facet::Facet(array<Point^> ^ vertices, System::Drawing::Color color)
{
	this->vertices = vertices;
	this->color = color;
}

Facet::Facet(array<Point^> ^ vertices) : Facet::Facet(vertices, System::Drawing::Color::Black) {}

Facet::Facet(Point ^ p1, Point ^ p2, Point ^ p3) : Facet::Facet(gcnew array<Point^>(3)) 
{
	//TODO?: можно обойтись без тела?
	vertices[0] = p1;
	vertices[1] = p2;
	vertices[2] = p3;
}

Facet::Facet() : Facet::Facet(gcnew Point(), gcnew Point(), gcnew Point()) {}

void Facet::draw(Bladestick::ZBuffer ^ buffer)
{
	buffer->drawLine(System::Drawing::Pens::Aqua, vertices[0], vertices[1]);
	buffer->drawLine(System::Drawing::Pens::Aqua, vertices[1], vertices[2]);
	buffer->drawLine(System::Drawing::Pens::Aqua, vertices[2], vertices[0]);
}

array<Point^> ^ Facet::getVertices()
{
	return vertices;
}

void Facet::setVertices(array<Point^> ^ vertices)
{
	this->vertices = vertices;
}

System::Drawing::Color Facet::getColor()
{
	return color;
}

void Facet::setColor(System::Drawing::Color color)
{
	this->color = color;
}
