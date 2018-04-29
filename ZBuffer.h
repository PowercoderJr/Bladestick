#pragma once

#include "Point.h"
#include "IDrawable.h"

namespace Bladestick
{
	namespace Drawing
	{
		public ref class ZBuffer
		{
		private:
			System::Drawing::Bitmap ^ bitmap;
			array<double> ^ zbuffer;
			System::Drawing::Color ^ bgColor;
			int width;
			int height;

		public:
			/*static const int MAX_WIDTH = 1920;
			static const int MAX_HEIGHT = 1080;*/

			ZBuffer(int width, int height, System::Drawing::Color ^ bgColor);
			ZBuffer(int width, int height);
			ZBuffer();
			void setSize(int width, int height);
			int getWidth();
			int getHeight();
			void clear();
			void drawToBuffer(IDrawable ^ drawable);
			void render(System::Drawing::Graphics ^ g);
			void setPixel(int x, int y, double z, System::Drawing::Color ^ color);
			void drawLine(System::Drawing::Color ^ color, double x0, double y0, double z0, double x1, double y1, double z1);
			void drawLine(System::Drawing::Color ^ color, Geometry::Point ^ p1, Geometry::Point ^ p2);
			System::Drawing::Color ^ getBgColor();
			void setBgColor(System::Drawing::Color ^ color);
		};

	}
}
