#pragma once

#include "Point.h"
#include "IDrawable.h"

namespace Bladestick
{
	namespace Drawing
	{
		namespace Geometry
		{
			public ref class Facet : public ITransformable, public IDrawable
			{
			internal:
				array<Point^> ^ vertices;  //3 �������
				System::Drawing::Color ^ color;

			public:
				static const int N_VERTICES = 3;
				Facet(array<Point^> ^ vertices, System::Drawing::Color ^ color);
				Facet(array<Point^> ^ vertices);
				Facet(Point ^ p1, Point ^ p2, Point ^ p3, System::Drawing::Color ^ color);
				Facet(Point ^ p1, Point ^ p2, Point ^ p3);
				Facet();
				virtual void draw(ZBuffer ^ buffer);
				array<Point^> ^ getVertices();
				void setVertices(array<Point^> ^ vertices);
				System::Drawing::Color ^ getColor();
				void setColor(System::Drawing::Color ^ color);
			};
		}
	}
}
