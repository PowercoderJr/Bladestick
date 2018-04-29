#pragma once

#include "Facet.h"
#include "IUpdatable.h"
#include "ZBuffer.h"
#include "IDrawable.h"

namespace Bladestick
{
	namespace Drawing
	{
		namespace Geometry
		{
			public ref class Box : public ITransformable, public IUpdatable, public IDrawable
			{
			internal:
				Point ^ corner1;
				Point ^ corner2;
				array<Point^> ^ vertices;  //8 вершин
				array<Facet^> ^ facets;  //12 треугольников
				double width;
				double length;
				double height;
				System::Drawing::Color ^ color;

			public:
				static const int N_VERTICES = 8;
				static const int N_FACETS = 12;

				Box(Point ^ bottomCenter, double width, double length, double height, System::Drawing::Color ^ color);
				Box(Point ^ corner1, Point ^ corner2, System::Drawing::Color ^ color);
				virtual void update();
				virtual void draw(Bladestick::Drawing::ZBuffer ^ buffer);
				void updatePoints();
				void updateFacets();
				double getWidth();
				void setWidth(double width);
				double getLength();
				void setLength(double length);
				double getHeight();
				void setHeight(double height);
				array<Point^> ^ getVertices();
				array<Facet^> ^ getFacets();
			};
		}
	}
}
