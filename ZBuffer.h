#pragma once

#include "Point.h"

namespace Bladestick
{
	public ref class ZBuffer
	{
	private:
		value struct Pixel
		{
			double z;
			System::Drawing::Pen ^ pen;
		};

		array<Pixel, 2> ^ buffer;
		System::Drawing::Pen ^ bgPen;

		void setPixel(int x, int y, Pixel pixel);

	public:
		static const int MAX_WIDTH = 1920;
		static const int MAX_HEIGHT = 1080;

		ZBuffer(System::Drawing::Pen ^ bgPen);
		ZBuffer();
		void clearArea(int w, int h);
		void render(System::Drawing::Graphics ^ g, int w, int h);
		void drawLine(System::Drawing::Pen ^ pen, double x0, double y0, double z0, double x1, double y1, double z1);
		void drawLine(System::Drawing::Pen ^ pen, Geometry::Point ^ p1, Geometry::Point ^ p2);
		System::Drawing::Pen ^ getBgPen();
		void setBgPen(System::Drawing::Pen ^ bgPen);
	};

}
