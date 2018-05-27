#include "Scene.h"
#include "Utils.h"
#include "Matrix.h"

using namespace Bladestick::Drawing;
using namespace System::Drawing;
using namespace System;

Scene::Scene(int width, int height, Color bgColor, Color edgeColor)
{
	setSize(width, height);
	this->bgColor = bgColor;
	this->edgeColor = edgeColor;
	this->camera = gcnew Camera(gcnew Vector3D(0, 0, 100), gcnew Vector3D(0, 0, 0), 1, 10000, 60, false);
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
	double ninf = Double::NegativeInfinity;
	for (int i = 0; i < width; ++i)
		for (int j = 0; j < height; ++j)
			zbuffer[index++] = ninf;
	Graphics ^ g = Graphics::FromImage(bitmap);
	g->Clear(bgColor);
	delete g;
}

bool Scene::isPointVisible(Vector3D ^ p)
{
	return p->mx >= 0 && p->mx <= width && p->my >= 0 && p->my <= height && p->mz <= -camera->near && p->mz >= -camera->far;
}

void Scene::setPixel(int x, int y, double z, Color color)
{
	if (x < 1 || x >= width || y < 1 || y >= height) return;

	int index = x * height + y;
	if (z >= zbuffer[index])
	{
		zbuffer[index] = z;
		//bitmap->SetPixel(x, camera->perspective ? y : height - y, color);
		bitmap->SetPixel(x, height - y, color);
	}
}

void Scene::drawLine(double x0, double y0, double z0, double x1, double y1, double z1, Color color)
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
			setPixel(y, x, z, color);
		else
			setPixel(x, y, z, color);
		error2 += derror2;
		z += zStep;

		if (error2 > dx)
		{
			y += diry;
			error2 -= dx * 2;
		}
	}
}

void Scene::drawLine(Vector3D ^ p1, Vector3D ^ p2, Color color)
{
	drawLine(p1->mx, p1->my, p1->mz, p2->mx, p2->my, p2->mz, color);
}

void Scene::drawTriangle(Vector3D ^ p1, Vector3D ^ p2, Vector3D ^ p3, Color color, char drawFlags)
{
	if (cmpDoubles(p1->my, p2->my) == 0 && cmpDoubles(p2->my, p3->my) == 0) return;
	if (!(isPointVisible(p1) && isPointVisible(p2) && isPointVisible(p3))) return;

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
		drawTriangle(p1, p2, breakPoint, color, drawFlags);
		drawTriangle(breakPoint, p2, p3, color, drawFlags);
	}
	else
	{
		//Заливка
		if ((drawFlags & DrawFlags::DRAW_FILL) > 0)
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
					setPixel(leftX + j, p1->my + i, mz, color);
				}
			}
		}

		//Контур
		if ((drawFlags & DrawFlags::DRAW_EDGES) > 0)
		{
			drawLine(p1, p2, edgeColor);
			drawLine(p2, p3, edgeColor);
			drawLine(p3, p1, edgeColor);
		}
	}
}

void Scene::drawToBuffer(SceneObject ^ obj, char drawFlags, bool useRandomPalette)
{
	int vCount = obj->vertices->Length;
	array<Vector3D ^> ^ vertices = gcnew array<Vector3D ^>(vCount);
	for (int i = 0; i < vCount; ++i)
		vertices[i] = obj->vertices[i]->clone();
	for each (Vector3D ^ v in vertices)
	{
		double xOffset = v->mx - camera->position->x;
		double yOffset = v->my - camera->position->y;
		double zOffset = v->mz - camera->position->z;
		v->mx = camera->rightDir->x * xOffset + camera->rightDir->y * yOffset + camera->rightDir->z * zOffset;
		v->my = camera->upDir->x * xOffset + camera->upDir->y * yOffset + camera->upDir->z * zOffset;
		v->mz = camera->backDir->x * xOffset + camera->backDir->y * yOffset + camera->backDir->z * zOffset;

		double aspect = (double)width / height;
		double vfov = camera->fov / aspect;
		double ctg = 1 / Math::Tan(vfov / 2);
		double n = camera->near, f = camera->far;
		if (camera->perspective)
		{			
			//VER_1
			/*v->mw = v->mz;
			v->mx = ctg / aspect * v->mx;
			v->my = ctg * v->my;
			v->mz = (2 * f * n / (n - f) + (f + n) / (f - n) * v->mz);*/
			//-

			//VER_2
			double hfov = camera->fov;
			double vfov = hfov / width * height;
			float r = Math::Tan(degToRad(hfov / 2));
			float l = -r;
			float t = Math::Tan(degToRad(vfov / 2));
			float b = -t;
			Vector3D ^ src = v->clone();
			v->mw = src->mz;
			v->mx = (2 * src->mx * n) / (-l + r) + (src->mz * (l + r)) / (l - r);
			v->my = -(2 * src->my * n) / (-b + t) + (src->mz * (b + t)) / (b - t);
			v->mz = -((2 * f * n) / (f - n)) + (src->mz * (f + n)) / (f - n);
			//-

			if (v->mw != 1)
			{
				v->mx /= v->mw;
				v->my /= v->mw;
				//v->mz /= v->mw;
			}

			v->mx = (v->mx + 1) * this->width / 2;
			v->my = (v->my + 1) * this->height / 2;
			//v->mz = v->mz * (camera->far - camera->near);
			int i = 1;
		}
		else
		{
			//Нужно ли искажение X и Y?
			/*v->mx = -ctg / aspect * v->mx;
			v->my = -ctg * v->my;*/
			v->mz = -(2 * f * n / (n - f) + (f + n) / (f - n) * v->mz);
			v->mx += width / 2;
			v->my += height / 2;
		}
	}

	Random ^ rnd = gcnew Random();
	for (int i = 0; i < obj->indices->Length; i += 3)
	{
		drawTriangle(vertices[obj->indices[i] - 1],
			vertices[obj->indices[i + 1] - 1],
			vertices[obj->indices[i + 2] - 1],
			useRandomPalette ? Color::FromArgb(rnd->Next(256), rnd->Next(256), rnd->Next(256)) : obj->colors[i / 3],
			drawFlags);
	}
}

void Scene::drawToBuffer(SceneObject ^ obj, char drawFlags)
{
	drawToBuffer(obj, drawFlags, false);
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
