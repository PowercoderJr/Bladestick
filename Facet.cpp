#pragma once

#include "Facet.h"
#include "Utils.h"
#include "ZBuffer.h"

using namespace Bladestick::Drawing::Geometry;

Facet::Facet(array<Vector3D^> ^ vertices, System::Drawing::Color ^ color)
{
	this->vertices = vertices;
	this->color = color;
}

Facet::Facet(array<Vector3D^> ^ vertices) : Facet::Facet(vertices, System::Drawing::Color::Black) {}

Facet::Facet(Vector3D ^ p1, Vector3D ^ p2, Vector3D ^ p3, System::Drawing::Color ^ color) : Facet::Facet(gcnew array<Vector3D^>(3), color)
{
	//TODO?: можно обойтись без тела?
	vertices->SetValue(p1, 0);
	vertices->SetValue(p2, 1);
	vertices->SetValue(p3, 2);
}

Facet::Facet(Vector3D ^ p1, Vector3D ^ p2, Vector3D ^ p3) : Facet::Facet(p1, p2, p3, System::Drawing::Color::Black) {}

Facet::Facet() : Facet::Facet(gcnew Vector3D(), gcnew Vector3D(), gcnew Vector3D()) {}

void Facet::draw(Bladestick::Drawing::ZBuffer ^ buffer)
{
	if (cmpDoubles(vertices[0]->y, vertices[1]->y) == 0 && cmpDoubles(vertices[1]->y, vertices[2]->y) == 0) return;

	if (vertices[0]->y > vertices[1]->y) swap(vertices, 0, 1);
	if (vertices[0]->y > vertices[2]->y) swap(vertices, 0, 2);
	if (vertices[1]->y > vertices[2]->y) swap(vertices, 1, 2);

	if (cmpDoubles(vertices[0]->y, vertices[1]->y) != 0 && cmpDoubles(vertices[1]->y, vertices[2]->y) != 0)
	{
		double yRatio = (vertices[2]->y - vertices[0]->y) / (vertices[1]->y - vertices[0]->y);
		Vector3D ^ breakPoint = vertices[0] + (vertices[2] - vertices[0]) / yRatio;
		(gcnew Facet(vertices[0], vertices[1], breakPoint, color))->draw(buffer);
		(gcnew Facet(breakPoint, vertices[1], vertices[2], color))->draw(buffer);
	}
	else
	{
		//Контур
		/*System::Drawing::Color ^ edgeColor = System::Drawing::Color::White;
		buffer->drawLine(edgeColor, vertices[0], vertices[1]);
		buffer->drawLine(edgeColor, vertices[1], vertices[2]);
		buffer->drawLine(edgeColor, vertices[2], vertices[0]);*/

		int height = vertices[2]->y - vertices[0]->y;
		Vector3D ^leftSmaller, ^leftBigger, ^rightSmaller, ^rightBigger;
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
			int leftX = leftSmaller->x + (leftBigger->x - leftSmaller->x) * k;
			int rightX = rightSmaller->x + (rightBigger->x - rightSmaller->x) * k;
			int leftZ = leftSmaller->z + (leftBigger->z - leftSmaller->z) * k;
			int rightZ = rightSmaller->z + (rightBigger->z - rightSmaller->z) * k;
			int length = rightX - leftX;
			for (int j = 0; j <= length; j++)
			{
				double k2 = (double)j / length;
				double z = leftZ + (rightZ - leftZ) * k2;
				buffer->setPixel(leftX + j, vertices[0]->y + i, z, color);
			}
		}
	}
}

void Facet::move(double x, double y, double z)
{
	throw gcnew System::NotImplementedException();
}

void Facet::scale(double a, double b, double c)
{
	throw gcnew System::NotImplementedException();
}

void Facet::rotate(double alpha, double beta, double gamma)
{
	throw gcnew System::NotImplementedException();
}

array<Vector3D^> ^ Facet::getVertices()
{
	return vertices;
}

void Facet::setVertices(array<Vector3D^> ^ vertices)
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
