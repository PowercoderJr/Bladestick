#pragma once

#include "Facet.h"
#include "Utils.h"
#include "ZBuffer.h"

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

//TODO: пересмотреть со введением Z
void Facet::draw(Bladestick::Drawing::ZBuffer ^ buffer)
{
	if (cmpDoubles(vertices[0]->y, vertices[1]->y) == 0 && cmpDoubles(vertices[1]->y, vertices[2]->y) == 0) return;

	if (vertices[0]->y > vertices[1]->y) swap(vertices, 0, 1);
	if (vertices[0]->y > vertices[2]->y) swap(vertices, 0, 2);
	if (vertices[1]->y > vertices[2]->y) swap(vertices, 1, 2);

	if (cmpDoubles(vertices[0]->y, vertices[1]->y) != 0 && cmpDoubles(vertices[1]->y, vertices[2]->y) != 0)
	{
		double yRatio = (vertices[2]->y - vertices[0]->y) / (vertices[1]->y - vertices[0]->y);
		Point ^ breakPoint = vertices[0] + (vertices[2] - vertices[0]) / yRatio;
		(gcnew Facet(vertices[0], vertices[1], breakPoint, color))->draw(buffer);
		(gcnew Facet(breakPoint, vertices[1], vertices[2], color))->draw(buffer);
	}
	else
	{
		//Контур
		System::Drawing::Color ^ edgeColor = System::Drawing::Color::White;
		buffer->drawLine(edgeColor, vertices[0], vertices[1]);
		buffer->drawLine(edgeColor, vertices[1], vertices[2]);
		buffer->drawLine(edgeColor, vertices[2], vertices[0]);

		int height = vertices[2]->y - vertices[0]->y;
		Point ^leftSmaller, ^leftBigger, ^rightSmaller, ^rightBigger;
#pragma region Узнаю кто левый-правый-верхний-нижний
		if (cmpDoubles(vertices[0]->y, vertices[1]->y) == 0)
		{
			leftBigger = rightBigger = vertices[2];
			if (vertices[0]->x < vertices[1]->x)
			{
				leftSmaller = vertices[0];
				rightSmaller = vertices[1];
			}
			else
			{
				leftSmaller = vertices[1];
				rightSmaller = vertices[0];
			}
		}
		else
		{
			leftSmaller = rightSmaller = vertices[0];
			if (vertices[1]->x < vertices[2]->x)
			{
				leftBigger = vertices[1];
				rightBigger = vertices[2];
			}
			else
			{
				leftBigger = vertices[2];
				rightBigger = vertices[1];
			}
		}
#pragma endregion

		for (int i = 0; i <= height; i++)
		{
			double k = (double)i / height;
			Point ^ A = leftSmaller + (leftBigger - leftSmaller) * k;
			Point ^ B = rightSmaller + (rightBigger - rightSmaller) * k;
			for (int j = A->x; j <= B->x; j++)
				buffer->setPixel(j, vertices[0]->y + i, 0, color);
		}
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
