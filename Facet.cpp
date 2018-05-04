#pragma once

#include "Facet.h"
#include "Utils.h"
#include "ZBuffer.h"
#include "Vector3D.h"

using namespace Bladestick::Drawing::Geometry;

Facet::Facet(array<Vector3D^> ^ vertices, System::Drawing::Color ^ color) : SceneObject::SceneObject()
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
	if (cmpDoubles(vertices[0]->my, vertices[1]->my) == 0 && cmpDoubles(vertices[1]->my, vertices[2]->my) == 0) return;

	if (vertices[0]->my > vertices[1]->my) swap(vertices, 0, 1);
	if (vertices[0]->my > vertices[2]->my) swap(vertices, 0, 2);
	if (vertices[1]->my > vertices[2]->my) swap(vertices, 1, 2);

	if (cmpDoubles(vertices[0]->my, vertices[1]->my) != 0 && cmpDoubles(vertices[1]->my, vertices[2]->my) != 0)
	{
		double yRatio = (vertices[2]->my - vertices[0]->my) / (vertices[1]->my - vertices[0]->my);
		Vector3D ^ breakPoint = gcnew Vector3D();
		breakPoint->mx = vertices[0]->mx + (vertices[2]->mx - vertices[0]->mx) / yRatio;
		breakPoint->my = vertices[0]->my + (vertices[2]->my - vertices[0]->my) / yRatio;
		breakPoint->mz = vertices[0]->mz + (vertices[2]->mz - vertices[0]->mz) / yRatio;
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

		int height = vertices[2]->my - vertices[0]->my;
		Vector3D ^leftSmaller, ^leftBigger, ^rightSmaller, ^rightBigger;
#pragma region Узнаю кто левый-правый-верхний-нижний
		if (cmpDoubles(vertices[0]->my, vertices[1]->my) == 0)
		{
			leftBigger = rightBigger = vertices[2];
			if (vertices[0]->mx < vertices[1]->mx)
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
			if (vertices[1]->mx < vertices[2]->mx)
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
			int leftX = leftSmaller->mx + (leftBigger->mx - leftSmaller->mx) * k;
			int rightX = rightSmaller->mx + (rightBigger->mx - rightSmaller->mx) * k;
			int leftZ = leftSmaller->mz + (leftBigger->mz - leftSmaller->mz) * k;
			int rightZ = rightSmaller->mz + (rightBigger->mz - rightSmaller->mz) * k;
			int length = rightX - leftX;
			for (int j = 0; j <= length; j++)
			{
				double k2 = (double)j / length;
				double mz = leftZ + (rightZ - leftZ) * k2;
				buffer->setPixel(leftX + j, vertices[0]->my + i, mz, color);
			}
		}
	}
}

void Facet::setPosition(double x, double y, double z)
{
	for each (Vector3D ^ vertex in vertices)
		vertex->setPosition(x, y, z);
}

void Facet::setOrigin(double x, double y, double z)
{
	SceneObject::setOrigin(x, y, z);
	for each (Vector3D ^ vertex in vertices)
		vertex->setOrigin(x, y, z);
}

void Facet::setScalingFactors(double a, double b, double c)
{
	SceneObject::setScalingFactors(a, b, c);
	for each (Vector3D ^ vertex in vertices)
		vertex->setScalingFactors(a, b, c);
}

void Facet::setRotationAngles(double alphaDeg, double betaDeg, double gammaDeg)
{
	SceneObject::setRotationAngles(alphaDeg, betaDeg, gammaDeg);
	for each (Vector3D ^ vertex in vertices)
		vertex->setRotationAngles(alphaDeg, betaDeg, gammaDeg);
}

void Facet::transform()
{
	for each (Vector3D ^ vertex in vertices)
		vertex->transform();
}

/*void Facet::scale(double a, double b, double c)
{
	throw gcnew System::NotImplementedException();
}

void Facet::rotate(double alphaDeg, double betaDeg, double gammaDeg)
{
	for each (Vector3D ^ vector in vertices)
		vector->rotate(alphaDeg, betaDeg, gammaDeg);
}*/

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
