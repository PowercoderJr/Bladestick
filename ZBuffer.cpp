#include "ZBuffer.h"
#include "Utils.h"

using namespace Bladestick::Drawing;
using namespace System::Drawing;

ZBuffer::ZBuffer(int width, int height, Color ^ bgColor)
{
	this->width = width > MAX_WIDTH ? MAX_WIDTH : width;
	this->height = height > MAX_HEIGHT ? MAX_HEIGHT : height;
	this->bitmap = gcnew Bitmap(this->width, this->height);
	this->zbuffer = gcnew array<double>(this->width * this->height);
	this->bgColor = bgColor;
}

ZBuffer::ZBuffer(int width, int height) : ZBuffer::ZBuffer(width, height, Color::Black) {}

ZBuffer::ZBuffer() : ZBuffer::ZBuffer(600, 400) {}

void ZBuffer::setSize(int width, int height)
{
	this->width = width > MAX_WIDTH ? MAX_WIDTH : width;
	this->height = height > MAX_HEIGHT ? MAX_HEIGHT : height;
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
	for (int i = 0; i < width; ++i)
		for (int j = 0; j < height; ++j)
		{
			zbuffer[i * height + j] = System::Double::NegativeInfinity;
			bitmap->SetPixel(i, j, *bgColor);
		}
}

void ZBuffer::render(System::Drawing::Graphics ^ g)
{
	g->DrawImage(bitmap, 0, 0, width, height);
}

void ZBuffer::setPixel(int x, int y, double z, Color ^ color)
{
	if (x < 0 || x > MAX_WIDTH || y < 0 || y > MAX_HEIGHT) return;

	int index = x * height + y;
	if (z > zbuffer[index])
	{
		zbuffer[index] = z;
		bitmap->SetPixel(x, y, *color);
	}
}

void ZBuffer::drawLine(Color ^ color, double x0, double y0, double z0, double x1, double y1, double z1)
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
	int derror2 = System::Math::Abs(dy) * 2;
	int error2 = 0;
	int y = y0;
	for (int x = x0; x <= x1; x++)
	{
		if (steep)
			setPixel(y, x, 0, color);
		else
			setPixel(x, y, 0, color);
		error2 += derror2;

		if (error2 > dx) {
			y += (y1 > y0 ? 1 : -1);
			error2 -= dx * 2;
		}
	}
}

void ZBuffer::drawLine(Color ^ color, Bladestick::Drawing::Geometry::Point ^ p1, Bladestick::Drawing::Geometry::Point ^ p2)
{
	ZBuffer::drawLine(color, p1->x, p1->y, p1->z, p2->x, p2->y, p2->z);
}

Color ^ ZBuffer::getBgColor()
{
	return this->bgColor;
}

void ZBuffer::setBgColor(Color ^ color)
{
	this->bgColor = color;
}
