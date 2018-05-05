#include "ZBuffer.h"
#include "Utils.h"

using namespace Bladestick::Drawing;
using namespace System::Drawing;

ZBuffer::ZBuffer(int width, int height, Color ^ bgColor, System::Drawing::Color ^ edgeColor)
{
	setSize(width, height);
	this->bgColor = bgColor;
	this->edgeColor = edgeColor;
}

ZBuffer::ZBuffer(int width, int height) : ZBuffer::ZBuffer(width, height, Color::Black, Color::White) {}

ZBuffer::ZBuffer() : ZBuffer::ZBuffer(600, 400) {}

void ZBuffer::setSize(int width, int height)
{
	this->width = width < 1 ? 1 : width;
	this->height = height < 1 ? 1 : height;
	this->bitmap = gcnew Bitmap(this->width, this->height);
	this->zbuffer = gcnew array<double>(this->width * this->height);
}

int ZBuffer::getWidth()
{
	return width;
}

int ZBuffer::getHeight()
{
	return height;
}

void ZBuffer::clear()
{
	int index = 0;
	double ninf = System::Double::NegativeInfinity;
	for (int i = 0; i < width; ++i)
		for (int j = 0; j < height; ++j)
			zbuffer[index++] = ninf;
		Graphics ^ g = Graphics::FromImage(bitmap);
		g->Clear(*bgColor);
		delete g;
}

void ZBuffer::setPixel(int x, int y, double z, Color ^ color)
{
	//if (x < 0 || x >= MAX_WIDTH || y < 0 || y >= MAX_HEIGHT) return;
	if (x < 0 || x >= width || y < 0 || y >= height) return;

	int index = x * height + y;
	if (z > zbuffer[index])
	{
		zbuffer[index] = z;
		bitmap->SetPixel(x, y, *color);
	}
}

void ZBuffer::drawLine(double x0, double y0, double z0, double x1, double y1, double z1, Color ^ color)
{
	bool steep = false;
	if (System::Math::Abs(x0 - x1) < System::Math::Abs(y0 - y1))
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
	double zStep = (z1 - z0) / dx;//System::Math::Sqrt(dx * dx + dy * dy);
	int derror2 = System::Math::Abs(dy) * 2;
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

void ZBuffer::drawLine(Vector3D ^ p1, Vector3D ^ p2, Color ^ color)
{
	drawLine(p1->mx, p1->my, p1->mz, p2->mx, p2->my, p2->mz, color);
}

void ZBuffer::drawTriangle(Vector3D ^ p1, Vector3D ^ p2, Vector3D ^ p3, System::Drawing::Color ^ color, bool drawEdges)
{
	if (cmpDoubles(p1->my, p2->my) == 0 && cmpDoubles(p2->my, p3->my) == 0) return;

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
		drawTriangle(p1, p2, breakPoint, color, drawEdges);
		drawTriangle(breakPoint, p2, p3, color, drawEdges);
	}
	else
	{
		//Контур
		if (drawEdges)
		{
			drawLine(p1, p2, edgeColor);
			drawLine(p2, p3, edgeColor);
			drawLine(p3, p1, edgeColor);
		}

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
}

void ZBuffer::drawToBuffer(SceneObject ^ obj, bool drawEdges)
{
	for (int i = 0; i < obj->indices->Length; i += 3)
	{
		drawTriangle(obj->vertices[obj->indices[i] - 1], obj->vertices[obj->indices[i + 1] - 1], obj->vertices[obj->indices[i + 2] - 1], obj->colors[i / 3], drawEdges);
	}
}

void ZBuffer::drawToBuffer(SceneObject ^ obj)
{
	drawToBuffer(obj, false);
}

void ZBuffer::render(Graphics ^ g)
{
	g->DrawImage(bitmap, 0, 0, width, height);
}

Color ^ ZBuffer::getBgColor()
{
	return this->bgColor;
}

void ZBuffer::setBgColor(Color ^ color)
{
	this->bgColor = color;
}
