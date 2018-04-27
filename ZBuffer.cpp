#include "ZBuffer.h"

using namespace Bladestick;

template <typename T> void swap(T * a, T * b);

ZBuffer::ZBuffer(System::Drawing::Pen ^ bgPen)
{
	this->buffer = gcnew array<Pixel, 2>(MAX_WIDTH, MAX_HEIGHT);
	this->bgPen = bgPen;
}

ZBuffer::ZBuffer() : ZBuffer::ZBuffer(System::Drawing::Pens::Black) {}

void ZBuffer::clearArea(int w, int h)
{
	for (int i = 0; i < w; ++i)
		for (int j = 0; j < h; ++j)
		{
			buffer[i, j].z = System::Double::NegativeInfinity;
			buffer[i, j].pen = bgPen;
		}
}

void ZBuffer::render(System::Drawing::Graphics ^ g, int w, int h)
{
	for (int i = 0; i < w; ++i)
		for (int j = 0; j < h; ++j)
			g->DrawLine(buffer[i, j].pen, i, j, i+1, j+1);
}

void Bladestick::ZBuffer::setPixel(int x, int y, Pixel pixel)
{
	if (pixel.z > buffer[x, y].z)
		buffer[x, y] = pixel;
}

void ZBuffer::drawLine(System::Drawing::Pen ^ pen, double x0, double y0, double z0, double x1, double y1, double z1)
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
		Pixel pixel;
		pixel.z = 0;
		pixel.pen = pen;
		if (steep)
			setPixel(y, x, pixel);
		else
			setPixel(x, y, pixel);
		error2 += derror2;

		if (error2 > dx) {
			y += (y1 > y0 ? 1 : -1);
			error2 -= dx * 2;
		}
	}
}

void ZBuffer::drawLine(System::Drawing::Pen ^ pen, Geometry::Point ^ p1, Geometry::Point ^ p2)
{
	ZBuffer::drawLine(pen, p1->x, p1->y, p1->z, p2->x, p2->y, p2->z);
}

System::Drawing::Pen ^ ZBuffer::getBgPen()
{
	return bgPen;
}

void ZBuffer::setBgPen(System::Drawing::Pen ^ bgPen)
{
	this->bgPen = bgPen;
}

template <typename T> void swap(T * a, T * b)
{
	double h = *a;
	*a = *b;
	*b = h;
}
