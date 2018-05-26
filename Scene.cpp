#include "Scene.h"
#include "Utils.h"

using namespace Bladestick::Drawing;
using namespace System::ComponentModel;
using namespace System::Drawing;
using namespace System;

Scene::Scene(int width, int height, Color bgColor, Color edgeColor)
{
	setSize(width, height);
	this->bgColor = bgColor;
	this->edgeColor = edgeColor;
	this->camera = {gcnew Vector3D(0, 0, -1000), gcnew Vector3D(0, 0, 0), -5000, 5000, false};
	this->objects = gcnew BindingList<SceneObject ^>();
}

Scene::Scene(int width, int height) : Scene::Scene(width, height, Color::Black, Color::White) {}

Scene::Scene() : Scene::Scene(600, 400) {}

void Scene::setSize(int width, int height)
{
	this->width = width < 1 ? 1 : width;
	this->height = height < 1 ? 1 : height;
	this->bitmap = gcnew Bitmap(this->width, this->height);
	this->zbuffer = gcnew array<double>(this->width * this->height);
}

int Scene::getWidth()
{
	return width;
}

int Scene::getHeight()
{
	return height;
}

void Scene::clear()
{
	int index = 0;
	double ninf = Double::PositiveInfinity;
	for (int i = 0; i < width; ++i)
		for (int j = 0; j < height; ++j)
			zbuffer[index++] = ninf;
		Graphics ^ g = Graphics::FromImage(bitmap);
		g->Clear(bgColor);
		delete g;
}

void Scene::setPixel(int x, int y, double z, Color color, bool flipVertical)
{
	if (x < 1 || x >= width || y < 1 || y >= height) return;

	int index = x * height + y;
	if (z <= zbuffer[index])
	{
		zbuffer[index] = z;
		bitmap->SetPixel(x, flipVertical ? height - y : y, color);
	}
}

void Scene::drawLine(double x0, double y0, double z0, double x1, double y1, double z1, Color color, bool flipVertical)
{
	bool steep = false;
	if (Math::Abs(x0 - x1) < Math::Abs(y0 - y1))
	{
		swap(&x0, &y0);
		swap(&x1, &y1);
		steep = true;
	}
	if (x0 > x1)
	{
		swap(&x0, &x1);
		swap(&y0, &y1);
	}
	int dx = x1 - x0;
	int dy = y1 - y0;
	int y = y0;
	double z = z0;
	double zStep = (z1 - z0) / dx;
	int derror2 = Math::Abs(dy) * 2;
	int error2 = 0;
	int diry = y1 > y0 ? 1 : -1;
	for (int x = x0; x <= x1; x++)
	{
		if (steep)
			setPixel(y, x, z, color, flipVertical);
		else
			setPixel(x, y, z, color, flipVertical);
		error2 += derror2;
		z += zStep;

		if (error2 > dx)
		{
			y += diry;
			error2 -= dx * 2;
		}
	}
}

void Scene::drawLine(Vector3D ^ p1, Vector3D ^ p2, Color color, bool flipVertical)
{
	drawLine(p1->mx, p1->my, p1->mz, p2->mx, p2->my, p2->mz, color, flipVertical);
}

void Scene::drawTriangle(Vector3D ^ p1, Vector3D ^ p2, Vector3D ^ p3, Color color, bool flipVertical, bool drawFill, bool drawEdges)
{
	if (cmpDoubles(p1->my, p2->my) == 0 && cmpDoubles(p2->my, p3->my) == 0) return;
	if (p1->mz < camera.near || p1->mz > camera.far) return;
	if (p2->mz < camera.near || p2->mz > camera.far) return;
	if (p3->mz < camera.near || p3->mz > camera.far) return;

	if (p1->my > p2->my) swap(&p1, &p2);
	if (p1->my > p3->my) swap(&p1, &p3);
	if (p2->my > p3->my) swap(&p2, &p3);

	if (cmpDoubles(p1->my, p2->my) != 0 && cmpDoubles(p2->my, p3->my) != 0)
	{
		double yRatio = (p3->my - p1->my) / (p2->my - p1->my);
		Vector3D ^ breakPoint = gcnew Vector3D();
		breakPoint->mx = p1->mx + (p3->mx - p1->mx) / yRatio;
		breakPoint->my = p1->my + (p3->my - p1->my) / yRatio;
		breakPoint->mz = p1->mz + (p3->mz - p1->mz) / yRatio;
		drawTriangle(p1, p2, breakPoint, color, flipVertical, drawFill, drawEdges);
		drawTriangle(breakPoint, p2, p3, color, flipVertical, drawFill, drawEdges);
	}
	else
	{
		//Заливка
		if (drawFill)
		{
			int height = p3->my - p1->my;
			Vector3D ^leftSmaller, ^leftBigger, ^rightSmaller, ^rightBigger;
#pragma region Узнаю кто левый-правый-верхний-нижний
			if (cmpDoubles(p1->my, p2->my) == 0)
			{
				leftBigger = rightBigger = p3;
				if (p1->mx < p2->mx)
				{
					leftSmaller = p1;
					rightSmaller = p2;
				}
				else
				{
					leftSmaller = p2;
					rightSmaller = p1;
				}
			}
			else
			{
				leftSmaller = rightSmaller = p1;
				if (p2->mx < p3->mx)
				{
					leftBigger = p2;
					rightBigger = p3;
				}
				else
				{
					leftBigger = p3;
					rightBigger = p2;
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
					setPixel(leftX + j, p1->my + i, mz, color, flipVertical);
				}
			}
		}

		//Контур
		if (drawEdges)
		{
			drawLine(p1, p2, edgeColor, flipVertical);
			drawLine(p2, p3, edgeColor, flipVertical);
			drawLine(p3, p1, edgeColor, flipVertical);
		}
	}
}

void Scene::drawToBuffer(SceneObject ^ obj, bool flipVertical, bool drawFill, bool drawEdges, bool useRandomPalette)
{
	Random ^ rnd = gcnew Random();
	for (int i = 0; i < obj->indices->Length; i += 3)
	{
		drawTriangle(obj->vertices[obj->indices[i] - 1],
			obj->vertices[obj->indices[i + 1] - 1],
			obj->vertices[obj->indices[i + 2] - 1],
			useRandomPalette ? Color::FromArgb(rnd->Next(256), rnd->Next(256), rnd->Next(256)) : obj->colors[i / 3],
			flipVertical, drawFill, drawEdges);
	}
}

void Scene::drawToBuffer(SceneObject ^ obj, bool flipVertical, bool drawFill, bool drawEdges)
{
	drawToBuffer(obj, flipVertical, drawFill, drawEdges, false);
}

void Scene::drawToBuffer(SceneObject ^ obj, bool flipVertical)
{
	drawToBuffer(obj, flipVertical, true, false);
}

void Scene::render(Graphics ^ g)
{
	g->DrawImage(bitmap, 0, 0, width, height);
}

Color Scene::getBgColor()
{
	return this->bgColor;
}

void Scene::setBgColor(Color color)
{
	this->bgColor = color;
}
